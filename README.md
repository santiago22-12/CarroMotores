# CarroMotores

Control de dos motores DC con un puente H (L298N) desde un STM32F401CCU6 (HSI 16 MHz).

| Señal | Pin | Entrada del L298N |
|---|---|---|
| M_IZQ_EN | PB0 | ENA |
| M_IZQ_A | PB1 | IN1 |
| M_IZQ_B | PB10 | IN2 |
| M_DER_EN | PB12 | ENB |
| M_DER_A | PB13 | IN3 |
| M_DER_B | PB14 | IN4 |

## Movimientos
| Movimiento | Motor izquierdo | Motor derecho |
|---|---|---|
| Avanzar | adelante (IN1) | adelante (IN4) |
| Retroceder | atrás (IN2) | atrás (IN3) |
| Girar derecha | adelante | atrás |
| Girar izquierda | atrás | adelante |
| Frenar | IN1=IN2=1 | IN3=IN4=1 |

## Cómo está hecho
- `Core/Librerias/motores.c`: cada movimiento es un **patrón de 6 bits** en una tabla.
  `PatronABsrr()` lo convierte en un valor para el registro **BSRR**, así los 6 pines cambian al mismo tiempo con una sola escritura.
- `main.c`: la rutina del carro es un arreglo `rutinaCarro[]` de pasos (movimiento + duración). Para cambiar la secuencia solo se edita la tabla.

## Proteus
Pines del STM32 → entradas del L298 según la tabla. Motores en OUT1/OUT2 y OUT3/OUT4, y alimentación de motores aparte (VS).
