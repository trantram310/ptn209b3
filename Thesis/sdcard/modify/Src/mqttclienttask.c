/* Built-in C library includes ---------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Platform includes --------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "main.h"
#include "mqttclienttask.h"
#include "flash.h"
#include "rtc.h"
#include "usart.h"
#include "modbus_mqtt_bridge.h"
/* Network includes. */
//#include "MQTTClient.h"
#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"
#include "lwip/err.h"
/* Shared Variables ----------------------------------*/
osThreadId netMQTTTask;
extern osMessageQId xQueueControlHandle;
extern osMessageQId xQueueMessageHandle;
extern osSemaphoreId netMqttIpSemaphoreHandle;
extern osMessageQId xQueueDownlinkHandle;
extern osMessageQId xQueueUplinkHandle;
osMessageQId xQueueProvisionHandle; // HERE
extern network_param_t mqttHostParam;
extern network_param_t netParam;
extern uint32_t netId;

const char *mqtt_id = "NULL";
const char *mqtt_user = "yktdxpqb";
const char *mqtt_password = "VKCG6yboYrYd";
const uint16_t u16_mqtt_port = 	19613;
const char *tel_topic = "upstream/telemetry/606ff2e222c1752264934dbb";
const char *command = "downstream/command/606ff2e222c1752264934dbb";
const char *down_pro = "downstream/provision/606ff2e222c1752264934dbb";
const char *up_pro = "upstream/provision/606ff2e222c1752264934dbb";


void netmqttTask(void *arg);

/* Private Varianles*/
static uint8_t inpub_id;
/* Start implementation ------------------------------*/
static void mqtt_incoming_publish_cb(void *arg, const char *topic,u32_t tot_len) {

	printf("\r\n Incoming publish at topic %s with total length %u\n", topic,(unsigned int) tot_len);

	/* Decode topic sring into a user defined reference */
	if (strcmp(topic,down_pro) == 0) {
		inpub_id = 0;
	} else if (strcmp(topic,command) == 0) {
		/* All topics starting with 'A' might be handled at the same way */
		inpub_id = 1;}
}
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len,u8_t flags) {

	//printf("\r\n Incoming publish payload with length %d, flags %u\n", len,(unsigned int) flags);
	if (flags & MQTT_DATA_FLAG_LAST) {
		/* Last fragment of payload received (or whole part if payload fits receive bufferSee MQTT_VAR_HEADER_BUFFER_LEN)  */
		printf("\r\n mqtt_incoming_data_cb: %s\n", (const char *) data);
		if (inpub_id == 0) // provision
			mqtt_modbus_thread_down_provision((char*) data, len);
		if (inpub_id == 1) // command
			mqtt_modbus_thread_down_command((char*) data, len);
	} else {
		/* Handle fragmented payload, store in buffer, write to file or whatever */
	}
}

static void mqtt_sub_request_cb(void *arg, err_t result) {
	/* Just print the result code here for simplicity,
	 normal behaviour would be to take some action if subscribe fails like
	 notifying user, retry subscribe or disconnect from server */
	printf("Subscribe command result: %d\n", result);
}

static void mqtt_pro_request_cb(void *arg, err_t result) {
	/* Just print the result code here for simplicity,
	 normal behaviour would be to take some action if subscribe fails like
	 notifying user, retry subscribe or disconnect from server */
	printf("Subscribe provision result: %d\n", result);
}
void mqtt_connection_cb(mqtt_client_t *client, void *arg,mqtt_connection_status_t status) {

	printf("\r\n MQTT Status: %d \r\n", status);
	err_t err, err_p;
	char sub_topic[50];
	char pro_topic[50];
	memset(sub_topic, 0, sizeof(sub_topic));
	strcat(sub_topic, command);
	memset(pro_topic, 0, sizeof(pro_topic));
	strcat(pro_topic, down_pro);
	if (status == MQTT_CONNECT_ACCEPTED) {
		printf("\r\n mqtt_connection_cb: Successfully connected\n");
		/* Setup callback for incoming publish requests */
		mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb,mqtt_incoming_data_cb, arg);
		/* Subscribe to a topic named "subtopic" with QoS level 1, call mqtt_sub_request_cb with result */
		err = mqtt_subscribe(client,sub_topic, 1, mqtt_sub_request_cb, arg);
		if (err != ERR_OK) {
			printf("\r\nmqtt_subscribe telemetry return: %d\n", err);
		}
		err_p = mqtt_subscribe(client, pro_topic, 1, mqtt_pro_request_cb, arg);
		if (err_p != ERR_OK) {
			printf("\r\nmqtt_subscribe telemetry return: %d\n", err_p);
		}
	} else {
		printf("\r\nmqtt_connection_cb: Disconnected, reason: %d\n", status);
		ip4_addr_t broker_ipaddr;
		broker_ipaddr.addr = mqttHostParam.ip.idata;
		struct mqtt_connect_client_info_t mqtt_client_info;
		mqtt_client_info.client_id = mqtt_id;
		mqtt_client_info.client_user = mqtt_user;
		mqtt_client_info.client_pass = mqtt_password;
		mqtt_client_info.keep_alive = 1000;
		mqtt_client_info.will_topic = NULL;
		mqtt_client_info.will_qos = 1;
		mqtt_client_info.will_retain = 0;
		err_t er;
		er = mqtt_client_connect(client, &broker_ipaddr,u16_mqtt_port,mqtt_connection_cb, NULL, &mqtt_client_info);
		vTaskDelay(100);
		printf("\r\b MQTT Service started successfully \r\n");
		if (er == ERR_OK) {
			printf("\r\n Connect to the Server %d.%d.%d.%d",
					mqttHostParam.ip.cdata[0], mqttHostParam.ip.cdata[1],
					mqttHostParam.ip.cdata[2], mqttHostParam.ip.cdata[3]);
		} else {
			printf("\r\n Failed to connect to MQTT server with er: %d", er);
		}

		/* Its more nice to be connected, so try to reconnect */
//		example_do_connect(client);
	}
}
static void mqtt_pub_request_cb(void *arg, err_t result) {
	if (result != ERR_OK) {
		printf("\r\n Publish result: %d\n", result);
	} else {
//		printf("\r\n Published ");
	}
}
void netmqttTask(void *arg) {

	printf("\r\n netmqttTask \r\n");
	xQueueControl_t xQueueControl;
	uint8_t uiSysState;
	xQueueControl.xTask = netMQTTTask;
	/*Waiting for controller start this task*/
	do {
		osDelay(10);
		xQueuePeek(xQueueMessageHandle, &uiSysState, 0);
	}
	while (uiSysState != SYS_MQTT);
	xQueueReceive(xQueueMessageHandle, &uiSysState, 0);
	printf("\r\b MQTT Service starting \r\n");
	/*Starting initial*/
	err_t er;
	mqtt_client_t *mqtt_client; // HERE
	ip4_addr_t broker_ipaddr;
	broker_ipaddr.addr = mqttHostParam.ip.idata;
	struct mqtt_connect_client_info_t mqtt_client_info;
	mqtt_client_info.client_id = mqtt_id;
	mqtt_client_info.client_user = mqtt_user;
	mqtt_client_info.client_pass = mqtt_password;
	mqtt_client_info.keep_alive = 1000;
	mqtt_client_info.will_topic = NULL;
	mqtt_client_info.will_qos = 1;
	mqtt_client_info.will_retain = 0;
	mqtt_client = mqtt_client_new();
	er = mqtt_client_connect(mqtt_client, &broker_ipaddr,u16_mqtt_port,mqtt_connection_cb, NULL, &mqtt_client_info);
	vTaskDelay(100);
	printf("\r\b MQTT Service started successfully \r\n");
	if (er == ERR_OK) {
		printf("\r\n Connect to the Server %d.%d.%d.%d",
				mqttHostParam.ip.cdata[0], mqttHostParam.ip.cdata[1],
				mqttHostParam.ip.cdata[2], mqttHostParam.ip.cdata[3]);
	} else {
		printf("\r\n Failed to connect to MQTT server with er: %d", er);
	}
	/*Notify controller the starting is successful*/
	xQueueControl.xState = TASK_RUNNING;
	xQueueSend(xQueueControlHandle, &xQueueControl, 10);
	#define port_DEFAULT_DELAY 	1000
	/*a loop in mqtt_modbus_thread_up(); function*/
	char pub_topic[20];
	memset(pub_topic, 0, sizeof(pub_topic));
	strcat(pub_topic,tel_topic);
	mqtt_modbus_thread_up(mqtt_client, pub_topic, up_pro);
	while (1)
		;
}
