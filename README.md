# Atividade PICO_W

Esta atividade faz parte do curso Embarca Tech e tem como objetivo explorar as funcionalidades do microcontrolador PICO_W.

## Vídeo Demonstrativo
[![Assista ao vídeo demonstrativo](https://img.youtube.com/vi/tCuJLA-QZgg/0.jpg)](https://youtu.be/tCuJLA-QZgg)

## Descrição das Funções

### init_keypad
Inicializa os pinos do teclado matricial, configurando as colunas como saídas e as linhas como entradas com resistores pull-up.

### init_leds_and_buzzer
Inicializa os pinos dos LEDs e do buzzer, configurando-os como saídas e garantindo que todos estejam desligados inicialmente.

### get_key
Verifica qual tecla do teclado matricial foi pressionada, retornando o caractere correspondente do mapa de teclas.

### control_led_and_buzzer
Controla os LEDs e o buzzer com base na tecla pressionada. Cada tecla tem uma ação específica, como acender um LED ou tocar o buzzer.

### piscar_led_vermelho
Pisca o LED vermelho três vezes com um intervalo de 200ms.

### piscar_led_verde
Pisca o LED verde três vezes com um intervalo de 200ms.

### piscar_led_azul
Pisca o LED azul três vezes com um intervalo de 200ms.

### acionar_led_sequencia
Acende os LEDs vermelho, verde e azul em sequência, cada um por 1 segundo, e exibe mensagens de status no console.

## Conclusão

Com os conteúdos aprendidos, este foi o resultado da atividade. Considera-se que temos um fundamento na linguagem C e na utilização da biblioteca "pico/stdlib.h".
