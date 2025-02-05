# OneShot

# Controle de LEDs com Raspberry Pi Pico e Pico SDK

## Descrição
Este projeto implementa um sistema de temporização para acionamento de LEDs utilizando a biblioteca **Pico SDK**. O acionamento ocorre por meio de um **botão (pushbutton)**, iniciando uma sequência de ativação e desativação dos LEDs conforme um ciclo predefinido.

## Funcionamento
1. O sistema inicia com todos os LEDs desligados.
2. Quando o botão é pressionado, todos os LEDs são ligados simultaneamente.
3. Após 3 segundos:
   - O LED verde é desligado.
4. Após mais 3 segundos:
   - O LED vermelho é desligado.
5. Após mais 3 segundos:
   - O LED azul é desligado, retornando ao estado inicial.

A temporização é gerenciada pela função `add_alarm_in_ms()` do **Pico SDK**, garantindo o controle dos LEDs de forma assíncrona.

## Componentes Utilizados
- **Microcontrolador:** Raspberry Pi Pico
- **LEDs:** 3 LEDs (azul, vermelho e verde)
- **Resistores:** Resistores adequados para os LEDs
- **Botão (Pushbutton)**

## Pinos Utilizados
| Componente | Pino do Pico |
|------------|-------------|
| LED Azul   | GPIO 11     |
| LED Vermelho | GPIO 12   |
| LED Verde  | GPIO 13     |
| Botão     | GPIO 5      |


## Simulação
Para testar este projeto em um simulador, pode-se utilizar ferramentas como:
- **Proteus**
- **Fritzing**
- **Wokwi**


