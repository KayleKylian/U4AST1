  #include <stdio.h>
  #include "pico/stdlib.h"

  #define LINHAS 4
  #define COLUNAS 4
  #define LEDS 3
  #define RED 11
  #define GREEN 9
  #define BLUE 10
  const uint ledPins[LEDS] = {RED, GREEN, BLUE};

  char keys[LINHAS][COLUNAS] = {
    { '1', '2', '3', 'A' },
    { '4', '5', '6', 'B' },
    { '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' }
  };
  uint linhaPins[LINHAS] = { 26, 22, 21, 20 }; // Pins connected to R1, R2, R3, R4
  uint colunaPins[COLUNAS] = { 19, 18, 17, 16 }; // Pins connected to C1, C2, C3, C4
  void iniciarTeclado() {
      for (int i = 0; i < LINHAS; i++) {
          gpio_init(linhaPins[i]);
          gpio_set_dir(linhaPins[i], GPIO_OUT);
          gpio_put(linhaPins[i], 1);  // Desativar linha (estado HIGH)
      }

      for (int i = 0; i < COLUNAS; i++) {
          gpio_init(colunaPins[i]);
          gpio_set_dir(colunaPins[i], GPIO_IN);
          gpio_pull_up(colunaPins[i]);
      }

      // Inicializar LED
      for (int i = 0; i < 3 ; i++){
        gpio_init(ledPins[i]);
        gpio_set_dir(ledPins[i],GPIO_OUT);
        gpio_put(ledPins[i],0);
      }
  }

  // Função para escanear o teclado
  char teclaPressionada() {
      for (int i = 0; i < LINHAS; i++) {
          gpio_put(linhaPins[i], 0);  // Ativar linha atual

          for (int j = 0; j < COLUNAS; j++) {
              if (gpio_get(colunaPins[j]) == 0) {
                  gpio_put(linhaPins[i], 1);  // Desativar linha atual
                  return keys[i][j];  // Retornar o valor da tecla pressionada
              }
          }

          gpio_put(linhaPins[i], 1);  // Desativar linha atual
      }

      return '\0';  // Nenhuma tecla pressionada
  }
  void loop(){
    while(true){
      char key = teclaPressionada();
      switch (key)
      {
      case '1':
        gpio_put(RED,1);
        break;
      case '2':
        gpio_put(BLUE,1);
        break;
      case '3':
        gpio_put(GREEN,1);
        break;
      default:
        break;
      }
      sleep_ms(100);
    }
    
  }
  int main()
  {
    iniciarTeclado();
    loop();
    return 0;
  }