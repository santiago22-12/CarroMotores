/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Cabecera de main.c - CarroMotores
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* USER CODE BEGIN EM */

/* USER CODE END EM */

void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M_IZQ_EN_Pin GPIO_PIN_0
#define M_IZQ_EN_GPIO_Port GPIOB
#define M_IZQ_A_Pin GPIO_PIN_1
#define M_IZQ_A_GPIO_Port GPIOB
#define M_IZQ_B_Pin GPIO_PIN_10
#define M_IZQ_B_GPIO_Port GPIOB
#define M_DER_EN_Pin GPIO_PIN_12
#define M_DER_EN_GPIO_Port GPIOB
#define M_DER_A_Pin GPIO_PIN_13
#define M_DER_A_GPIO_Port GPIOB
#define M_DER_B_Pin GPIO_PIN_14
#define M_DER_B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
