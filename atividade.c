#include <stdio.h>
#include "pico/stdlib.h"

// PINOS DO TECLADO MATRICIAL (COLUNAS, LINHAS)
const uint8_t COL_PINS[] = {19, 18, 17, 16}; // Defina os pinos das colunas
const uint8_t ROW_PINS[] = {28, 27, 26, 20}; // Defina os pinos das linhas
// MAPA DE TECLAS
const char KEY_MAP[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// PINOS DOS LEDs
const uint LED_RED   = 11;
const uint LED_GREEN = 9;
const uint LED_BLUE  = 10;
// PINO BUZZER
const uint BUZZER = 2;

// PROTÓTIPOS DE FUNÇÕES
void init_keypad();
void init_leds_and_buzzer();
char get_key();
void control_led_and_buzzer(char key);
void piscarLEDVermelho();
void piscar_led_verde();
void piscar_led_azul();

// Entrada do Código
int main() {
    //stdio_init_all();
    init_keypad();
    init_leds_and_buzzer();
    printf("Sistema iniciado. Pressione as teclas do teclado.\n");

    while (true) {
        char key = get_key();
        if (key) {
            printf("Tecla pressionada: %c\n", key);
            control_led_and_buzzer(key);
        }
        sleep_ms(50); // Atraso para evitar sobrecarga
    }
    return 0;
}


// Função para inicializar o teclado matricial
void init_keypad() {
    for (int i = 0; i < 4; i++) {
        gpio_init(COL_PINS[i]);
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_OUT);
        gpio_put(COL_PINS[i], 1); // Desativa todas as colunas
        gpio_set_dir(ROW_PINS[i], GPIO_IN);
        gpio_pull_up(ROW_PINS[i]); // Ativa pull-up nas linhas
    }
}

// Função para inicializar os LEDs e o buzzer
void init_leds_and_buzzer() {
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_init(BUZZER);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(BUZZER, GPIO_OUT);

    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(BUZZER, 0);
}

// Função para verificar qual tecla foi pressionada
char get_key() {
    for (int col = 0; col < 4; col++) {
        gpio_put(COL_PINS[col], 0); // Ativa a coluna atual

        for (int row = 0; row < 4; row++) {
            if (gpio_get(ROW_PINS[row]) == 0) { // Verifica se a linha está baixa
                sleep_ms(50); // Debounce
                if (gpio_get(ROW_PINS[row]) == 0) { // Confirma tecla pressionada
                    while (gpio_get(ROW_PINS[row]) == 0); // Espera tecla ser liberada
                    gpio_put(COL_PINS[col], 1); // Desativa a coluna atual
                    return KEY_MAP[row][col]; // Retorna a tecla pressionada
                }
            }
        }

        gpio_put(COL_PINS[col], 1); // Desativa a coluna atual
    }
    return 0; // Nenhuma tecla pressionada
}

// Função para controlar os LEDs e o buzzer com base na tecla pressionada
void control_led_and_buzzer(char key) {
    // Reseta todos os LEDs e o buzzer
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(BUZZER, 0);

    switch (key) {
        case '1':
            gpio_put(LED_RED, 1); // Liga o LED vermelho
            break;
        case '2':
            gpio_put(LED_BLUE, 1); // Liga o LED azul
            break;
        case '3':
            gpio_put(LED_GREEN, 1); // Liga o LED verde
            break;
        case '4':
            piscarLEDVermelho();
            break;
        case '5':
            piscar_led_verde();
            break;
        case '6':
            piscar_led_azul();
            break;
        case '*':
            gpio_put(BUZZER, 1);
            sleep_ms(500); // Toca o buzzer por 500ms
            gpio_put(BUZZER, 0);
            break;
        default:
            printf("Tecla %c pressionada, sem ação definida.\n", key);
            break;
    }
}

void piscar_led_verde() {
    for (int i = 0; i < 3; i++) {
        gpio_put(LED_GREEN, 1);
        sleep_ms(200);
        gpio_put(LED_GREEN, 0);
        sleep_ms(200);
    }
}

void piscar_led_azul() {
    for (int i = 0; i < 3; i++) {
        gpio_put(LED_BLUE, 1);
        sleep_ms(200);
        gpio_put(LED_BLUE, 0);
        sleep_ms(200);
    }
}


// Funcao para piscar o led vermelho
void piscarLEDVermelho() {
    for (int i = 0; i < 3; i++) {
        gpio_put(LED_RED, 1);
        sleep_ms(200);
        gpio_put(LED_RED, 0);
        sleep_ms(200);
    }
}