#ifndef NUMEROS_H
#define NUMEROS_H

#include "controle_leds.h"
#include "hardware/pio.h"

// Define o valor usado para limpar a matriz
#define CLEAN 11

// Para uso das variáveis globais definidas em main.c
extern PIO pio_global;
extern uint sm_global;
extern bool estado_led_azul;
extern bool estado_led_verde;
extern  uint8_t valor;

#define TOTAL_LEDS 25

// Definição das cores (vetores com TOTAL_LEDS elementos)
double color_red_ativa[TOTAL_LEDS] =   {0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3};

double color_green_ativa[TOTAL_LEDS] = {0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3};

double color_blue_ativa[TOTAL_LEDS]  = {0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3,
                                        0.3, 0.3, 0.3, 0.3, 0.3};

double color_red_desativa[TOTAL_LEDS]  = {0.0, 0.0, 0.0, 0.0, 0.0,
                                           0.0, 0.0, 0.0, 0.0, 0.0,
                                           0.0, 0.0, 0.0, 0.0, 0.0,
                                           0.0, 0.0, 0.0, 0.0, 0.0,
                                           0.0, 0.0, 0.0, 0.0, 0.0};

double color_green_desativa[TOTAL_LEDS] = {0.0, 0.0, 0.0, 0.0, 0.0,
                                           0.0, 0.0, 0.0, 0.0, 0.0,
                                           0.0, 0.0, 0.0, 0.0, 0.0,
                                           0.0, 0.0, 0.0, 0.0, 0.0,
                                           0.0, 0.0, 0.0, 0.0, 0.0};

double color_blue_desativa[TOTAL_LEDS] = {0.0, 0.0, 0.0, 0.0, 0.0,
                                          0.0, 0.0, 0.0, 0.0, 0.0,
                                          0.0, 0.0, 0.0, 0.0, 0.0,
                                          0.0, 0.0, 0.0, 0.0, 0.0,
                                          0.0, 0.0, 0.0, 0.0, 0.0};

// Definição dos frames dos números (matriz 5x5) para os dígitos 0 a 9
uint zero[TOTAL_LEDS]   = {0,1,1,1,0,
                           0,1,0,1,0,
                           0,1,0,1,0,
                           0,1,0,1,0,
                           0,1,1,1,0};

uint um[TOTAL_LEDS]     = {0,0,1,0,0,
                           0,0,1,1,0,
                           1,0,1,0,0,
                           0,0,1,0,0,
                           0,0,1,0,0};

uint dois[TOTAL_LEDS]   = {0,1,1,1,0,
                           0,1,0,0,0,
                           0,1,1,1,0,
                           0,0,0,1,0,
                           0,1,1,1,0};

uint tres[TOTAL_LEDS]   = {0,1,1,1,0,
                           0,1,0,0,0,
                           0,1,1,1,0,
                           0,1,0,0,0,
                           0,1,1,1,0};

uint quatro[TOTAL_LEDS] = {0,1,0,1,0,
                           0,1,0,1,0,
                           0,1,1,1,0,
                           0,1,0,0,0,
                           0,0,0,1,0};

uint cinco[TOTAL_LEDS]  = {0,1,1,1,0,
                           0,0,0,1,0,
                           0,1,1,1,0,
                           0,1,0,0,0,
                           0,1,1,1,0};

uint seis[TOTAL_LEDS]   = {0,1,1,1,0,
                           0,0,0,1,0,
                           0,1,1,1,0,
                           0,1,0,1,0,
                           0,1,1,1,0};

uint sete[TOTAL_LEDS]   = {0,1,1,1,0,
                           0,1,0,0,0,
                           0,0,0,1,0,
                           0,1,0,0,0,
                           0,0,0,1,0};

uint oito[TOTAL_LEDS]   = {0,1,1,1,0,
                           0,1,0,1,0,
                           0,1,1,1,0,
                           0,1,0,1,0,
                           0,1,1,1,0};

uint nove[TOTAL_LEDS]   = {0,1,1,1,0,
                           0,1,0,1,0,
                           0,1,1,1,0,
                           0,1,0,0,0,
                           0,1,1,1,0};

// Se o valor for CLEAN (11) a matriz é limpa.
void exibir_numero(uint valor) {
    if (valor == CLEAN) {
        uint clear[TOTAL_LEDS] = {0};
        atualizar_matriz(clear, color_red_desativa, color_green_desativa, color_blue_desativa, pio_global, sm_global);
        return;
    }
    // Se o led azul estiver ligado, a matriz de leds apenas irá mostrar numeros azuis
    if (estado_led_azul == true && estado_led_verde==false){
            switch (valor) {
        case 0:
             atualizar_matriz(zero, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 1:
            atualizar_matriz(um, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 2:
            atualizar_matriz(dois, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 3:
            atualizar_matriz(tres, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 4:
            atualizar_matriz(quatro, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 5:
            atualizar_matriz(cinco, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 6:
            atualizar_matriz(seis, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 7:
            atualizar_matriz(sete, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 8:
            atualizar_matriz(oito, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 9:
            atualizar_matriz(nove, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        default:
            break;
       }
    }

    // Se o led verde estiver ligado, a matriz de leds apenas irá mostrar numeros verde
    if (estado_led_azul == false && estado_led_verde==true){
            switch (valor) {
        case 0:
             atualizar_matriz(zero, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 1:
            atualizar_matriz(um, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 2:
            atualizar_matriz(dois, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
        case 3:
            atualizar_matriz(tres, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 4:
            atualizar_matriz(quatro, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 5:
            atualizar_matriz(cinco, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 6:
            atualizar_matriz(seis, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 7:
            atualizar_matriz(sete, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
        case 8:
            atualizar_matriz(oito, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 9:
            atualizar_matriz(nove, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        default:
            break;
        }
    }


    if (estado_led_azul == true && estado_led_verde==true) {
            switch (valor) {
        case 0:
             atualizar_matriz(zero, color_red_desativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 1:
            atualizar_matriz(um, color_red_desativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 2:
            atualizar_matriz (dois, color_red_desativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 3:
            atualizar_matriz(tres, color_red_desativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 4:
            atualizar_matriz(quatro, color_red_desativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 5:
            atualizar_matriz(cinco, color_red_desativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 6:
            atualizar_matriz(seis, color_red_desativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 7:
            atualizar_matriz(sete, color_red_desativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 8:
            atualizar_matriz(oito, color_red_desativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 9:
            atualizar_matriz(nove, color_red_desativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        default:
            break;
        }
    }

    if (estado_led_azul==false && estado_led_verde==false){
    switch (valor) {
        case 0:
            atualizar_matriz(zero, color_red_ativa, color_green_desativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 1:
            atualizar_matriz(um, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 2:
            atualizar_matriz(dois, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 3:
            atualizar_matriz(tres, color_red_ativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 4:
            atualizar_matriz(quatro, color_red_ativa, color_green_desativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 5:
            atualizar_matriz(cinco, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 6:
            atualizar_matriz(seis, color_red_desativa, color_green_desativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 7:
            atualizar_matriz(sete, color_red_ativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        case 8:
            atualizar_matriz(oito, color_red_ativa, color_green_desativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 9:
            atualizar_matriz(nove, color_red_desativa, color_green_ativa, color_blue_desativa, pio_global, sm_global);
            break;
        case 10:
            // Estado especial: exibe todos os LEDs com cores ativas (pode ser alterado conforme desejado)
            atualizar_matriz(nove, color_red_ativa, color_green_ativa, color_blue_ativa, pio_global, sm_global);
            break;
        default:
            break;
    }
}

}

#endif
