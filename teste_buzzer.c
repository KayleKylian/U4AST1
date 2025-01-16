#include <stdio.h>
#include <pico/stdlib.h>

// PINOS DO TECLADO MATRICIAL (COLUNAS, LINHAS)
const uint8_t COL_PINS[] = {4, 3, 2, 28}; // GP4, GP3, GP2, GP28
const uint8_t ROW_PINS[] = {8, 7, 6, 5};  // GP8, GP7, GP6, GP5
// MAPA DE TECLAS
const char KEY_MAP[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// PINOS DOS LEDs
const uint LED_RED   = 13;   // GP13
const uint LED_GREEN = 11;   // GP11
const uint LED_BLUE  = 12;   // GP12
// PINO BUZZER
const uint BUZZER = 22; //GP22

// Função para inicializar os pinos do teclado
void init_keypad() {
    for (int i = 0; i < 4; i++) {
        gpio_init(COL_PINS[i]);
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_OUT);
        gpio_set_dir(ROW_PINS[i], GPIO_IN);
        gpio_pull_up(ROW_PINS[i]);
    }
}

// Função para inicializar os LEDs
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
        gpio_put(COL_PINS[col], 0); // Ativa coluna
        for (int row = 0; row < 4; row++) {
            if (gpio_get(ROW_PINS[row]) == 0) { // Detecta se a linha está baixa
                while (gpio_get(ROW_PINS[row]) == 0); // Espera tecla ser solta
                return KEY_MAP[row][col]; // Retorna a tecla pressionada
            }
        }
        gpio_put(COL_PINS[col], 1); // Desativa coluna
    }
    return 0; // Nenhuma tecla pressionada
}

// Função para controlar os LEDs com base na tecla pressionada
void control_led_and_buzzer(char key) {
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(BUZZER, 0);

    switch (key) {
        case '1':
            gpio_put(LED_RED, 1); // Liga o LED vermelho
            break;
        case '3':
            gpio_put(LED_GREEN, 1); // Liga o LED verde
            break;
        case '2':
            gpio_put(LED_BLUE, 1); // Liga o LED azul
            break;
        case 'A':
            gpio_put(LED_RED, 0);
            gpio_put(LED_GREEN, 0);
            gpio_put(LED_BLUE, 0); // Desliga todos os LEDs
            break;
        case '*':
            gpio_put(BUZZER, 1);
            sleep_ms(50);
            gpio_put(BUZZER, 0);
        default:
            break;
    }
}

int main() {
    //stdio_init_all();
    init_keypad();
    init_leds_and_buzzer();

    while (true) {
        char key = get_key();
        if (key) {
            printf("Tecla pressionada: %c\n", key);
            control_led_and_buzzer(key);
        }
        sleep_ms(50); // Para evitar debounce
    }

    return 0;
}
//teste