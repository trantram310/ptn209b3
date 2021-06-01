/*
 * SIM7600task.c
 *
 *  Created on: May 5, 2021
 *      Author: ACER
 */
/* Built-in C library includes ---------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
/* Platform includes --------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "main.h"
#include "sim7600.h"

/* Shared Variables ----------------------------------*/
osThreadId netSIMTask;
extern osMessageQId xQueueControlHandle;
extern osMessageQId xQueueMessageHandle;
extern osSemaphoreId netMqttIpSemaphoreHandle;
extern osMessageQId xQueueDownlinkHandle;
extern osMessageQId xQueueUplinkHandle;

char *client = "mqtt";
const char *server = "m14.cloudmqtt.com";
const char *mqtt_id = "NULL";
const char *mqtt_user = "yktdxpqb";
const char *mqtt_password = "VKCG6yboYrYd";
const uint16_t u16_mqtt_port = 	19613;
const char *tel_topic = "upstream/telemetry/608a78baaa969877dec4e6f4";
const char *pro_topic = "upstream/provision/608a78baaa969877dec4e6f4";
const char *command = "downstream/command/608a78baaa969877dec4e6f4";
const char *down_pro = "downstream/provision/608a78baaa969877dec4e6f4";

void netsimTask(void *arg);

void netsimTask(void *arg)
{
	//printf("\r\n netsimTask \r\n");
	xQueueControl_t xQueueControl;
	uint8_t uiSysState;
	xQueueControl.xTask = netSIMTask;
	/*Waiting for controller start this task*/
	do {
		osDelay(10);
		xQueuePeek(xQueueMessageHandle, &uiSysState, 0);
	}
	while (uiSysState != SYS_SIM_TASK);
	xQueueReceive(xQueueMessageHandle, &uiSysState, 0);
	//printf("\r\b SIM Service starting \r\n");
	/*Starting initial*/
	INIT_SIM7600();   // HERE
	sim7600_info_t sim7600_client;
	sim7600_client.client_id = mqtt_id;
	sim7600_client.client_user = mqtt_user;
	sim7600_client.client_pass = mqtt_password;
	sim7600_client.port= u16_mqtt_port;
	sim7600_client.keepalive = 1000;
	sim7600_client.will_topic = NULL;
	sim7600_client.qos = 1;
	sim7600_client.retain = 0;
	uint8_t state = SIM7600_NEW_CONNECTION(client,server,sim7600_client.client_user,sim7600_client.client_pass,sim7600_client.port,sim7600_client.keepalive);
	SIM7600_PUBLISH_PACKET(tel_topic,sim7600_client.qos);
	//vTaskDelay(100);
//	mqtt_client = mqtt_client_new();
//	er = mqtt_client_connect(mqtt_client, &broker_ipaddr,u16_mqtt_port,mqtt_connection_cb, NULL, &mqtt_client_info);
//	vTaskDelay(100);
//	printf("\r\b MQTT Service started successfully \r\n");
	if (state == 1) {
	} else {
		//printf("\r\n Failed to connect to MQTT server with er: %d", er);
	}
	/*Notify controller the starting is successful*/
	xQueueControl.xState = TASK_RUNNING;
	xQueueSend(xQueueControlHandle, &xQueueControl, 10);
	#define port_DEFAULT_DELAY 	1000
	/*a loop in mqtt_modbus_thread_up(); function*/
	//MQTT_SIM7600_UPSTREAM(tel_topic, pro_topic, sim7600_client.qos);
//	SIM7600_PUBLISH_PACKET(tel_topic,sim7600_client.qos);
	while (1)
		;
}
