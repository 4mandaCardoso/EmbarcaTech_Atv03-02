#include <stdio.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"      // Função reset_usb_boot para entrar em modo de gravação
#include "hardware/i2c.h"      // Comunicação via I²C
#include "hardware/pio.h"      // Controle de PIO para WS2812
#include "hardware/clocks.h"   // Configuração dos clocks do sistema

// Inclusão dos arquivos customizados – verifique se estão no caminho correto.
#include "inc/ssd1306.h"                 // Funções para manipulação do display OLED SSD1306
#include "inc/font.h"                    // Fonte para exibição de caracteres no display
#include "bibliotecas/controle_leds.h"   // Funções para controle da matriz de LEDs
#include "bibliotecas/numeros.h"         // Dados para exibição de números na matriz de LEDs
#include "matriz_de_leds.pio.h"          // Programa PIO para controlar os LEDs 

// =====================================================
// DEFINIÇÕES DE PINS E CONSTANTES
// =====================================================

// Configuração do I²C para o display OLED
#define I2C_PORT        i2c1         // Seleciona a porta I²C 1
#define I2C_SDA_PIN     14           // Pino SDA
#define I2C_SCL_PIN     15           // Pino SCL
#define DISPLAY_ADDR    0x3C         // Endereço I²C do display SSD1306

// Configuração para a matriz de LEDs
#define LED_MATRIZ_PIN  7            // Pino de controle da matriz de leds

// Configuração dos botões
#define BOTAO_A         5            // Pino do botão A
#define BOTAO_B         6            // Pino do botão B
#define BOTAO_JOY       22           // Pino do botão do joystick

// Tempo para o tratamento de debouncing (em microssegundos)
#define TEMPO_DEBOUNCE_US 200000     // 200ms

// Configuração dos LEDs indicadores
#define LED_VERMELHO    13           // Agora o LED indicador é o LED VERMELHO (pino 13)
#define LED_AZUL        12           // LED azul no pino 12
#define LED_VERDE       11           // LED verde no pino 11

// Variáveis de estado dos LEDs indicadores
bool estado_led_verde = false;     // Estado inicial: desligado
bool estado_led_azul = false;         // Estado inicial: desligado

// =====================================================
// VARIÁVEIS GLOBAIS DE DISPOSITIVOS
// =====================================================

// Estrutura do display OLED
ssd1306_t displayOLED;

// Variáveis para o PIO (matriz de LEDs)
// Estas variáveis são usadas por outras bibliotecas (como numeros.h) via declaração extern.
PIO pio_global = pio0;
uint sm_global = 0;

// =====================================================
// VARIÁVEIS PARA DEBOUNCE (TEMPO)
static volatile uint32_t tempo_ultimo_botaoA = 0;
static volatile uint32_t tempo_ultimo_botaoB = 0;

// =====================================================
// PROTÓTIPOS DAS FUNÇÕES
// =====================================================

/*
    handler_gpio: Trata as interrupções geradas pelos botões.
    Verifica qual botão foi pressionado, aplica debounce e executa a ação correspondente.
*/
static void handler_gpio(uint gpio, uint32_t eventos);

// =====================================================
// FUNÇÃO PRINCIPAL: MAIN
// =====================================================

int main(void)
{
    /*
       Inicialização geral:
         - Comunicação USB/serial (stdio)
         - I²C para o display OLED
         - Configuração do PIO para a matriz de LEDs WS2812
         - Inicialização de pinos para LEDs indicadores e botões com interrupção.
    */
    
    // Inicializa a comunicação serial para debug
    stdio_init_all();

    // Configuração do I²C
    i2c_init(I2C_PORT, 400000); // Frequência de 400 kHz
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    
    // Inicializa e configura o display OLED via função customizada
    ssd1306_init_config_clean(&displayOLED, I2C_SCL_PIN, I2C_SDA_PIN, I2C_PORT, DISPLAY_ADDR);
    
    // Configura o PIO para a matriz de LEDs WS2812
    uint offset = pio_add_program(pio_global, &matriz_de_leds_program);
    sm_global = pio_claim_unused_sm(pio_global, true);
    matriz_de_leds_program_init(pio_global, sm_global, offset, LED_MATRIZ_PIN);
    
    // Configuração dos LEDs indicadores
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    
    // Configuração dos botões: inicializa os pinos e habilita os pull-ups
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B);
    
    gpio_init(BOTAO_JOY);
    gpio_set_dir(BOTAO_JOY, GPIO_IN);
    gpio_pull_up(BOTAO_JOY);
    
    // Configura as interrupções para os botões (detecção de borda de descida)
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &handler_gpio);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &handler_gpio);
    gpio_set_irq_enabled_with_callback(BOTAO_JOY, GPIO_IRQ_EDGE_FALL, true, &handler_gpio);
    
    // Exibe mensagens iniciais no display OLED
    ssd1306_draw_string(&displayOLED, "LED GREEN: off", 10, 10);
    ssd1306_draw_string(&displayOLED, "LED BLUE: off", 10, 20);
    ssd1306_send_data(&displayOLED);
    
    // Desenha um retângulo no display (como contorno)
    ssd1306_rect(&displayOLED, 3, 3, 122, 58, true, false);
    ssd1306_send_data(&displayOLED);
    
    // Loop principal: verifica entrada USB e executa ações
    int valor;
    while (true) {
        if(stdio_usb_connected()){
            char c = getchar();
            
            if(isdigit(c)){
                //Escreve Número na matriz de leds
                sscanf(&c, "%d", &valor);
                print_number(valor,pio_global,sm_global);
                //Mostra o caractere no display Oled
                ssd1306_draw_string(&displayOLED,"Caractere:",10,35);
                ssd1306_draw_char(&displayOLED,c,90,35);
                //Mensagem no monitor serial;
                printf("Caractere Enviado: %c.\n",c); 
            }else{
                //Apaga se houver algum número na matriz de LEDS
                print_number(CLEAN,pio_global,sm_global);
                //Mostra o caractere no display Oled
                ssd1306_draw_string(&displayOLED,"Caractere:",10,35);
                ssd1306_draw_char(&displayOLED,c,90,35);
                //Mensagem no monitor serial;
                printf("Caractere Enviado: %c.\n",c); 
            }
            ssd1306_send_data(&displayOLED);

        }
    }

}

// =====================================================
// FUNÇÃO DE INTERROMPIMENTO (HANDLER) DOS BOTÕES
// =====================================================

/*
    handler_gpio: Esta função trata as interrupções dos botões.
    
    - Para BOTAO_A: alterna o estado do LED VERMELHO e atualiza o display.
    - Para BOTAO_B: alterna o estado do LED AZUL e atualiza o display.
    - Para BOTAO_JOY: limpa a matriz de LEDs e o display e reinicia o dispositivo em modo bootloader USB.
    
    A função utiliza controle de debounce comparando o tempo atual com o último acionamento.
*/
static void handler_gpio(uint gpio, uint32_t eventos)
{
    uint32_t tempo_atual = to_us_since_boot(get_absolute_time());
    
    if (gpio == BOTAO_A)
    {
        if (tempo_atual - tempo_ultimo_botaoA > TEMPO_DEBOUNCE_US)
        {
            tempo_ultimo_botaoA = tempo_atual;
            estado_led_verde = !estado_led_verde;
            gpio_put(LED_VERDE, estado_led_verde);
            
            if (estado_led_verde)
            {
                ssd1306_draw_string(&displayOLED, "LED GREEN: on ", 10, 10);
                printf("LED verde: LIGADO.\n");
            }
            else
            {
                ssd1306_draw_string(&displayOLED, "LED GREEN: off", 10, 10);
                printf("LED verde: DESLIGADO.\n");
            }
        }
    }
    
    if (gpio == BOTAO_B)
    {
        if (tempo_atual - tempo_ultimo_botaoB > TEMPO_DEBOUNCE_US)
        {
            tempo_ultimo_botaoB = tempo_atual;
            estado_led_azul = !estado_led_azul;
            gpio_put(LED_AZUL, estado_led_azul);
            
            if (estado_led_azul)
            {
                ssd1306_draw_string(&displayOLED, "LED BLUE: on ", 10, 20);
                printf("LED azul: LIGADO.\n");
            }
            else
            {
                ssd1306_draw_string(&displayOLED, "LED BLUE: off", 10, 20);
                printf("LED azul: DESLIGADO.\n");
            }
        }
    }
    
    if (gpio == BOTAO_JOY)
    {
        // Limpa a matriz de LEDs e o display, e reinicia o dispositivo em modo bootloader USB.
        print_number(CLEAN, pio_global, sm_global);
        ssd1306_fill(&displayOLED, false);
        ssd1306_send_data(&displayOLED);
        printf("Reiniciando a placa em modo de gravação.\n");
        reset_usb_boot(0, 0);
    }
    
    ssd1306_send_data(&displayOLED);
}
