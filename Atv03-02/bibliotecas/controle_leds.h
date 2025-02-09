#ifndef CONTROLE_LEDS_H
#define CONTROLE_LEDS_H

#include "hardware/pio.h"
#include "pico/stdlib.h"

#define TOTAL_LEDS 25

// Função para converter valores RGB (0 a 1) em um valor de 24 bits
static inline uint32_t get_color(double r, double g, double b) {
    unsigned char R = (unsigned char)(r * 255);
    unsigned char G = (unsigned char)(g * 255);
    unsigned char B = (unsigned char)(b * 255);
    return (G << 24) | (R << 16) | (B << 8);
}

// Função para atualizar a matriz de LEDs WS2812 com base nos dados fornecidos
static inline void atualizar_matriz(uint *art, double *red, double *green, double *blue, PIO pio, uint sm) {
    for (int i = 0; i < TOTAL_LEDS; i++) {
        uint32_t valor_led = get_color(red[24 - i], green[24 - i], blue[24 - i]);
        if (art[24 - i])
            pio_sm_put_blocking(pio, sm, valor_led);
        else
            pio_sm_put_blocking(pio, sm, 0);
    }
}

// Função print_number: exibe um número na matriz chamando exibir_numero (definida em numeros.h)
static inline void print_number(uint numero, PIO pio, uint sm) {
    // Para manter a compatibilidade, usamos exibir_numero
    extern void exibir_numero(uint numero);
    exibir_numero(numero);
}

#endif  // CONTROLE_LEDS_H