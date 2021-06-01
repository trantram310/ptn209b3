/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "stdint.h"
#include "stdio.h"
#include "command.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
extern uint32_t gotCommandFlag;
extern uint8_t commandBuffer[100];
extern uint32_t commandBufferIndex;
osMessageQId xQueueControlHandle;
osMessageQId xQueueMessageHandle;
osMessageQId xQueueDownlinkHandle;
osMessageQId xQueueUplinkHandle;
osMessageQId xQueueResetHandle;
/* USER CODE END Includes */
osThreadId netSIMTask;
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
osThreadId defaultTaskHandle;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void ResetHandlerTask(void *arg);
/* USER CODE END FunctionPrototypes */
extern void netsimTask(void const *arg);
void StartDefaultTask(void const * argument);
void MX_FREERTOS_Init(void);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of netMqttIpSemaphore */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of myTimer01 */
  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */

	osMessageQDef(xQueueControl, 1, xQueueControl_t);
	xQueueControlHandle = osMessageCreate(osMessageQ(xQueueControl), NULL);

	osMessageQDef(xQueueMessage, 1, uint8_t);
	xQueueMessageHandle = osMessageCreate(osMessageQ(xQueueMessage), NULL);

	osMessageQDef(xQueueDownlink, 1, xQueueMbMqtt_t);
	xQueueDownlinkHandle = osMessageCreate(osMessageQ(xQueueDownlink), NULL);

	osMessageQDef(xQueueUplink, 1, xQueueMbMqtt_t);
	xQueueUplinkHandle = osMessageCreate(osMessageQ(xQueueUplink), NULL);

	osMessageQDef(xQueueReset, 1, sizeof(uint32_t));
	xQueueResetHandle = osMessageCreate(osMessageQ(xQueueUplink), NULL);

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
}
  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
 void StartDefaultTask(void const * argument)
  {
    /* USER CODE BEGIN StartDefaultTask */
  	/*Create Task Modules in this line*/
  	/*SIm serive*/
  	osThreadDef(netSIMTask, netsimTask, osPriorityNormal, 0, 4 * 128);
  	netSIMTask = osThreadCreate(osThread(netSIMTask), NULL);
  	printf("\r\n MemFree: %d", xPortGetFreeHeapSize());

  	/*Controller*/
  	xQueueControl_t xQueueControl;
  	#define PORT_DEFAULT_DELAY	1000
  	uint8_t uiSysState = SYS_START;
  	uint8_t uiSysUpdate = FALSE;
  	BaseType_t sysError;
  	/* Infinite loop */
  	for (;;) {
  		switch (uiSysState) {
  		case SYS_START:
  			//printf("\r\n Task Controller: Implementing...  \r\n");
  			uiSysUpdate = TRUE;
  			uiSysState++;
  			break;
  		case SYS_SIM_TASK:
  			//printf("\r\n Starting netMQTTTask module:  \r\n");
  			sysError = xQueueReceive(xQueueControlHandle, &xQueueControl,portMAX_DELAY);
  			if (sysError == pdTRUE) {
  				if ((xQueueControl.xState == TASK_RUNNING) && (xQueueControl.xTask == netSIMTask)) {
  					//printf("\r\n Starting netMQTTTask module: OK \r\n");
  					uiSysUpdate = TRUE;
  					uiSysState++;
  				}
  			} else {
  					uiSysUpdate = TRUE;
  					uiSysState++;
  			}
  			break;
  		case SYS_DEFAULT:
  			if (gotCommandFlag) {
  				gotCommandFlag = 0;
  				memset(commandBuffer,'\0',sizeof(commandBuffer));
  			}
  			osDelay(10);
  			break;

  		}
  		if ((uiSysUpdate == TRUE) && (uiSysState != SYS_DEFAULT)) {
  			xQueueSend(xQueueMessageHandle, &uiSysState, 0);
  			uiSysUpdate = FALSE;
  		}
  //		osDelay(200);
  	}
    /* USER CODE END StartDefaultTask */
  }
  /* USER CODE END RTOS_THREADS */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
