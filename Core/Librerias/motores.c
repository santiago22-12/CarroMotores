/*
 * motores.c
 *
 * Implementación del control de los dos motores del carro.
 */

#include "motores.h"

/* Bits de cada salida dentro del patrón */
#define B_IZQ_EN   (1U << 0)
#define B_IZQ_A    (1U << 1)
#define B_IZQ_B    (1U << 2)
#define B_DER_EN   (1U << 3)
#define B_DER_A    (1U << 4)
#define B_DER_B    (1U << 5)

/* Pines físicos en el mismo orden de los bits (todos están en GPIOB) */
static const uint16_t pinesMotor[6] =
{
  M_IZQ_EN_Pin, M_IZQ_A_Pin, M_IZQ_B_Pin,
  M_DER_EN_Pin, M_DER_A_Pin, M_DER_B_Pin
};

typedef struct
{
  const char *nombre;
  uint8_t     patron;
} DefMovimiento;

/*
 * Tabla de verdad del puente H:
 *   Motor izquierdo: A=1,B=0 -> adelante | A=0,B=1 -> atrás
 *   Motor derecho  : va montado en espejo, por eso B=1 es adelante y A=1 atrás
 *   A=1, B=1 (con EN=1) -> freno
 */
static const DefMovimiento tablaMov[MOV_TOTAL] =
{
  /* AVANZAR: los dos motores hacia adelante */
  [MOV_AVANZAR]         = { "Avanzar",
                            B_IZQ_EN | B_IZQ_A | B_DER_EN | B_DER_B },
  /* RETROCEDER: los dos motores hacia atrás */
  [MOV_RETROCEDER]      = { "Retroceder",
                            B_IZQ_EN | B_IZQ_B | B_DER_EN | B_DER_A },
  /* GIRAR A LA DERECHA: izquierdo adelante, derecho atrás */
  [MOV_GIRAR_DERECHA]   = { "Girar derecha",
                            B_IZQ_EN | B_IZQ_A | B_DER_EN | B_DER_A },
  /* GIRAR A LA IZQUIERDA: izquierdo atrás, derecho adelante */
  [MOV_GIRAR_IZQUIERDA] = { "Girar izquierda",
                            B_IZQ_EN | B_IZQ_B | B_DER_EN | B_DER_B },
  /* FRENAR: todas las salidas en alto (freno activo del puente H) */
  [MOV_FRENAR]          = { "Frenar",
                            B_IZQ_EN | B_IZQ_A | B_IZQ_B | B_DER_EN | B_DER_A | B_DER_B },
};

/*
 * Convierte el patrón de 6 bits en un valor para BSRR:
 *   parte baja  (bits 0-15)  -> pines que se ponen en 1
 *   parte alta  (bits 16-31) -> pines que se ponen en 0
 */
static uint32_t PatronABsrr(uint8_t patron)
{
  uint32_t encender = 0;
  uint32_t apagar   = 0;
  uint32_t i;

  for (i = 0; i < 6U; i++)
  {
    if (patron & (1U << i))
    {
      encender |= pinesMotor[i];
    }
    else
    {
      apagar |= pinesMotor[i];
    }
  }
  return encender | (apagar << 16);
}

void Motores_Ejecutar(Movimiento mov)
{
  if (mov >= MOV_TOTAL)
  {
    mov = MOV_FRENAR;
  }
  M_IZQ_EN_GPIO_Port->BSRR = PatronABsrr(tablaMov[mov].patron);
}

void Motores_EjecutarPor(Movimiento mov, uint32_t duracion_ms)
{
  Motores_Ejecutar(mov);
  HAL_Delay(duracion_ms);
}

void Motores_Rutina(const PasoRutina *pasos, uint32_t cantidad)
{
  uint32_t i;

  for (i = 0; i < cantidad; i++)
  {
    Motores_EjecutarPor(pasos[i].movimiento, pasos[i].duracion_ms);
  }
}

const char *Motores_Nombre(Movimiento mov)
{
  return (mov < MOV_TOTAL) ? tablaMov[mov].nombre : "Desconocido";
}
