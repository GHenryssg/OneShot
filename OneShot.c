#include "pico/stdlib.h"
#include <stdio.h>

// Definição dos pinos dos LEDs e do botão
#define LED_BLUE 11
#define LED_RED 12
#define LED_GREEN 13
#define BUTTON 5

// Variável para controlar o estado dos LEDs
typedef enum {
    ALL_ON,   // Todos os LEDs ligados
    TWO_ON,   // Dois LEDs ligados
    ONE_ON,   // Apenas um LED ligado
    ALL_OFF   // Todos os LEDs desligados
} LedState;

LedState current_state = ALL_OFF;
bool button_pressed = false;

// Função de callback para o temporizador
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    switch (current_state) {
        case ALL_ON:
            // Transição para DOIS ligados: desliga o LED verde
            gpio_put(LED_GREEN, 0);
            current_state = TWO_ON;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            break;
        case TWO_ON:
            // Transição para APENAS UM ligado: desliga o LED vermelho
            gpio_put(LED_RED, 0);
            current_state = ONE_ON;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            break;
        case ONE_ON:
            // Transição para TODOS DESLIGADOS: desliga o LED azul
            gpio_put(LED_BLUE, 0);
            current_state = ALL_OFF;
            break;
        case ALL_OFF:
            // Nada a fazer
            break;
    }
    return 0;
}

// Função de callback para o botão
void button_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON && current_state == ALL_OFF) {
        button_pressed = true;
    }
}

int main() {
    // Inicializa a stdio para usar a porta serial
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Configura o pino do botão como entrada
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    // Configura a interrupção para o botão
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    // Loop principal
    while (true) {
        if (button_pressed && current_state == ALL_OFF) {
            button_pressed = false;

            // Inicia a sequência: todos os LEDs ligados
            current_state = ALL_ON;
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_RED, 1);
            gpio_put(LED_GREEN, 1);

            // Configura o primeiro alarme para 3 segundos
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        }
        sleep_ms(100);
    }

    return 0;
}