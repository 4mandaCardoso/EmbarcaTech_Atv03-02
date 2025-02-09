## PROJETO - Interfaces de Comunicação Serial com RP2040
**(SUB GRUPO 6 - ATIVIDADE DA AULA SÍNCRONA 03/02)**

───────────────────────────────────────────────

*Idealizadora do Projeto:*  
**AMANDA CARDOSO LOPES**

───────────────────────────────────────────────

## OBJETIVO DO PROJETO

───────────────────────────────────────────────

Este projeto tem como finalidade consolidar os conceitos sobre interfaces de comunicação serial no RP2040 e explorar as funcionalidades da placa de desenvolvimento BitDogLab. O projeto foca na implementação prática dos protocolos UART e I2C, no controle de LEDs comuns e LEDs endereçáveis WS2812, no uso de botões de acionamento com interrupções e debounce, e na integração de hardware e software. O programa **deve seguir os seguintes requisitos:**

1. **Uso de Interrupções:**  
   - Todas as funcionalidades relacionadas aos botões devem ser implementadas utilizando rotinas de interrupção (IRQ).

2. **Debouncing:**  
   - Implementação obrigatória do tratamento de bouncing dos botões via software.

3. **Controle de LEDs:**  
   - Uso de LEDs comuns e LEDs WS2812 para demonstrar diferentes tipos de controle.

4. **Utilização do Display SSD1306:**  
   - Exibição de caracteres maiúsculos e minúsculos para demonstrar o uso correto da biblioteca e do protocolo I2C.

5. **Envio de Informações via UART:**  
   - Envio e recepção de dados pelo Serial Monitor.

6. **Organização do Código:**  
   - O código deve estar bem estruturado e comentado para facilitar o entendimento.

───────────────────────────────────────────────

## FUNCIONALIDADES DO PROJETO

───────────────────────────────────────────────

1. **Interação com o Botão A:**  
   - Ao pressionar o Botão A o led verde acende 
   - A operação é registrada de duas formas:
     - Mensagem no display SSD1306.
     - Texto descritivo enviado ao Serial Monitor.

2. **Interação com o Botão B:**  
   - Ao pressionar o Botão B o led azul acende 
   - A operação é registrada de duas formas:
     - Mensagem no display SSD1306.
     - Texto descritivo enviado ao Serial Monitor.

3. **Entrada de caracteres via PC:**
   -  Ao digitar algum caracter via Serial Monitor do VS Code, o caracter é registrado de duas formas:
     - Exibição do caractere digitado no display SSD1306.
     - Texto descritivo enviado ao Serial monitor
   - Para números entre 0 e 9, exibição de símbolos correspondentes na matriz de LEDs (5x5).
  **Atenção** : há uma adição importante nesse projeto, feito por mim : Se algum led estiver ligado, o número exibido na matriz terá a cor do led que estiver ligado. **(EXTRA)**

4. **Estado bootsel no joystick (EXTRA)**
   -  Ao pressionar o joystick, a plaquinha entra em modo bootsel, o display se apaga, qualquer representação na matriz de leds é apagada, assim como o led rgb e a bitdoglab fica pronta para receber outro programa.

───────────────────────────────────────────────

## COMPONENTES UTILIZADOS

───────────────────────────────────────────────

### Elementos Comuns (para ambas as atividades)
- **Microcontrolador:** Raspberry Pi Pico W.
- **Resistores:** 3 unidades de 330 Ω (para limitar a corrente dos LEDs).
- **Fios de Conexão:**  
  - Fio Verde para o negativo.  
  - Fio Preto para o positivo.

### Atividade 1 – Semáforo
- **LEDs:**  
  - LED Vermelho, LED Amarelo e LED Verde, conectados aos GPIOs 11, 12 e 13 (utilizando o LED RGB disponível no BitDogLab).

### Atividade 2 – Temporizador One-Shot
- **LEDs:**  
  - LED Azul, LED Vermelho e LED Verde, conectados aos GPIOs 12, 13 e 11 (usando o LED RGB do BitDogLab).  
- **Botão:**  
  - BOTÃO_A, conectado ao GPIO 5, utilizado para iniciar a sequência temporizada.

───────────────────────────────────────────────

## COMPONENTES UTILIZADOS

───────────────────────────────────────────────

- **Linguagem:** C  
- **Componentes Eletrônicos:**  
- *Microcontrolador:* Placa BitDogLab (RP2040).
- *Matriz 5x5 de LEDs:* Conectada à GPIO 7.
- *LED RGB:* Conectado às GPIOs 11, 12 e 13.
- *Botões:*
  - Botão A - GPIO 5.
  - Botão B - GPIO 6.
- *Display SSD1306:* Conectado via I2C (GPIO 14 e GPIO 15).

───────────────────────────────────────────────

## COMO EXECUTAR O PROJETO?

───────────────────────────────────────────────


### VIA VSCODE

1. **Configuração Inicial:**  
   - Abra o projeto no VS Code 
   - Clone o Repositório:
     ```sh
     git init
     git clone https://github.com/4mandaCardoso/EmbarcaTech_Atv03-02.git
     ```  

2. **Carregamento e Compilação:**  
   - Compile o código e gere o arquivo .UF2.

3. **Rodando na plaquinha:**  
   - Arraste o arquivo .UF2 para o diretório da plaquinha.


───────────────────────────────────────────────

## VÍDEO DE DEMONSTRAÇÃO 

───────────────────────────────────────────────

### Link do vídeo:
🔗 https://drive.google.com/drive/folders/1YkUD66tpQaCAf7ZsSYGDZQAp95dNAiKx?usp=drive_link

───────────────────────────────────────────────

## CONCLUSÃO

───────────────────────────────────────────────

Esse trabalho foi bem importante para o meu aprendizado, porque me ajudou a aplicar na prática o que eu tinha aprendido sobre comunicação serial e controle de hardware com microcontroladores. Trabalhar com interfaces como UART, SPI e I2C me deu uma visão melhor de como os dispositivos se comunicam. Além disso, as tarefas que envolviam controlar LEDs, botões e tratar interrupções foram ótimas para melhorar minha habilidade de programar e resolver problemas. O projeto também me ajudou a entender como integrar hardware e software, principalmente com a placa BitDogLab. Trabalhar com LEDs WS2812, displays I2C e comunicação UART foi essencial para entender como fazer tudo funcionar direitinho. No fim, esse desafio foi muito bom para consolidar o que eu aprendi, tanto do ponto de vista técnico quanto na hora de organizar o código de forma mais eficiente.

───────────────────────────────────────────────

*Desenvolvido por: Amanda Cardoso Lopes*
