/*
 * motores.h
 *
 * Control de dos motores DC con un puente H (tipo L298N).
 *
 *   Motor izquierdo: M_IZQ_EN (ENA), M_IZQ_A (IN1), M_IZQ_B (IN2)
 *   Motor derecho  : M_DER_EN (ENB), M_DER_A (IN3), M_DER_B (IN4)
 *
 * Cada movimiento es un "patrón" de 6 bits que se escribe en el puerto de una
 * sola vez con el registro BSRR, así todas las salidas cambian al mismo tiempo.
 */

#ifndef LIBRERIAS_MOTORES_H_
#define LIBRERIAS_MOTORES_H_

#include <stdint.h>
#include "main.h"

typedef enum
{
  MOV_AVANZAR = 0,
  MOV_RETROCEDER,
  MOV_GIRAR_DERECHA,
  MOV_GIRAR_IZQUIERDA,
  MOV_FRENAR,
  MOV_TOTAL
} Movimiento;

typedef struct
{
  Movimiento movimiento;
  uint32_t   duracion_ms;
} PasoRutina;

void        Motores_Ejecutar(Movimiento mov);
void        Motores_EjecutarPor(Movimiento mov, uint32_t duracion_ms);
void        Motores_Rutina(const PasoRutina *pasos, uint32_t cantidad);
const char *Motores_Nombre(Movimiento mov);

#endif /* LIBRERIAS_MOTORES_H_ */
