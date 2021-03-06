/* Built-in C library includes ---------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <param.h>
/* Platform includes --------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "main.h"
#include "mqttclienttask.h"
#include "flash.h"
#include "rtc.h"
#include "usart.h"
#include "json.h"
#include "modbus_mqtt_bridge.h"
#include "mbproto.h"

/* Network includes----------------------------*/
#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"
#include "err.h"
#include "lwip.h"
#include "lwip/init.h"
#include "lwip/netif.h"

#include "command.h"
#include "http_client.h"
#include "param.h"
#include "time_value.h"


/* Shared Variables --------------------------*/
extern osMessageQId xQueueDownlinkHandle;
extern osMessageQId xQueueUplinkHandle;
/* Private Variables -------------------------*/
const char *pro_topic="upstream/provision/606ff2e222c1752264934dbb";
uint8_t mqtt_couter_err = 0;
char buffer[100];
char temp[20];
char temp1[20];
char temp2[20];
char temp3[20];
static data1_t *ptr;
data1_t test;
/* Start implementation ----------------------*/

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start
			&& strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}
/*---------------------------------------------------PARSING DARA-----------------------------------------------------------------------------*/
data1_t *parse_device(char *Buffer, uint16_t BufferLen)
{
	ptr = &test;
	int i,r;
	jsmn_parser p;
	jsmntok_t t[JSON_MAX_LEN]; /* We expect no more than JSON_MAX_LEN tokens */
	jsmn_init(&p);
	r = jsmn_parse(&p, Buffer,BufferLen, t,sizeof(t) / sizeof(t[0]));
	for (i = 1; i < r; i++) {
		if (jsoneq(Buffer, &t[i], "PORT") == 0) {
			(ptr)->channel = atoi(Buffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "ID") == 0) {
			(ptr)->deviceID = atoi(Buffer + t[i + 1].start);
			i++;
		} else if (jsoneq(Buffer, &t[i], "FC") == 0) {
			(ptr)->func = atoi(Buffer + t[i + 1].start);
			i++;

		} else if (jsoneq(Buffer, &t[i], "CHANNEL") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->deviceChannel = (uint16_t)strtol(temp, NULL, 0);
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICETYPE") == 0) {
			//char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->deviceType = temp;
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICENAME") == 0) {
			//char temp[20];
			memset(temp1,'\0',sizeof(temp));
			strncpy(temp1,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->deviceName = temp1;
			i++;
		} else if (jsoneq(Buffer, &t[i], "CHANNELTITLE") == 0) {
			//char temp[20];
			memset(temp2,'\0',sizeof(temp2));
			strncpy(temp2,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->channeltitle = temp2;
			i++;
		}else if (jsoneq(Buffer, &t[i], "VALUETYPE") == 0) {
			//char temp[20];
			memset(temp3,'\0',sizeof(temp3));
			strncpy(temp3,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->valueType= temp3;
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICESTATUS") == 0) {
			(ptr)->devicestatus = atoi(Buffer + t[i + 1].start);
			i++;
		}
	}
	return ptr;
}

void addDevice(data1_t *destination, data1_t *data)
{
   destination->channel = data->channel;
   destination->deviceID = data->deviceID;
   destination->func = data->func;
   destination->devicestatus = data->devicestatus;
   destination->deviceChannel = data->deviceChannel;
   destination->deviceType = strdup(data->deviceType); // return NULL means fail
   destination->deviceName = strdup(data->deviceName);
   destination->channeltitle = strdup(data->channeltitle);
   destination->valueType = strdup(data->valueType);

}
/*---------------------------------------------------MODBUS MQTT BRIGDE FUNCTION-----------------------------------------------------------------------------*/
static void mqtt_bridge_pub_request_cb(void *arg, err_t result) {
	if (result != ERR_OK) {
		printf("\r\n Publish result: %d\n", result);
	} else {
//		printf("\r\n Published ");
	}
}
/**@ Brief: Get data from modbus dev and forward it to mqtt server
 * @ Todo:
 * 		Parse json object from server
 * */
void mqtt_modbus_thread_up(mqtt_client_t *client, char *pub_topic,char *pro_topic) {

//	uint8_t main_time[6];
//	BaseType_t Err = pdFALSE;
//	xQueueMbMqtt_t xQueueMbMqtt;
//	portCHAR publish_buffer[MAX_JSON_LEN];
//	portCHAR publish_provision[100];
//	err_t err;
//	while (1) {
//		Err = xQueueReceive(xQueueUplinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME*3);
//		if (Err == pdPASS) {
//			if (xQueueMbMqtt.gotflagProvision == 1 && xQueueMbMqtt.sum_dev != 0)
//				{
//					uint16_t SUM = xQueueMbMqtt.sum_dev ;
//					err_t err;
//					for (uint16_t i = 0 ; i < SUM; i = i + 1)
//					{
//						memset(publish_provision, 0, 100);
//			//			createJson_provision(publish_provision,table1[i].name_dev,table1[i].type,table1[i].name);  // HERE
//						err = mqtt_publish(client,pro_topic, publish_provision,strlen(publish_provision), QOS_0, 0,mqtt_bridge_pub_request_cb,NULL);
//						if (err != ERR_OK) {
//							printf("\r\n Publish_Provision err: %d\n", err);
//						}
//						osDelay(100);
//					}
//					//xQueueMbMqtt.mutex = 1;
//					xQueueMbMqtt.gotflagProvision = 0;
//					BaseType_t er = pdFALSE;
//					er = xQueueSend(xQueueDownlinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
//					if (er == pdPASS) {
//					}
//				} // END OF SENDING PROVISION
//			dem ++;
//			memset(buffer,0,100);
//			/*Create Json and publish to mqtt */
//			Get_Time(main_time);
//			//createJson(buffer,chan,table[xQueueMbMQtt.countflag].name,table[xQueueMbMQtt.countflag].name_dev, xQueueMbMQtt.RegData.i16data, main_time);
////			createJson_v1(buffer,table1[xQueueMbMqtt.countflag].name_dev, xQueueMbMqtt.RegData.i16data, main_time);
//			if (dem < 4)
//				{
//					strcat(buffer,",");
//				}
//			strcat(publish_buffer,buffer);
//			/*publish to mqtt */
//			if (dem == 4)
//			{
//				strcat(publish_buffer,"}");
//				err = mqtt_publish(client, pub_topic, publish_buffer,strlen(publish_buffer), QOS_0, 0,mqtt_bridge_pub_request_cb,NULL);
//				memset(publish_buffer, 0, MAX_JSON_LEN);
//				strcat(publish_buffer,"{");
//				dem = 0;
//				if (err != ERR_OK) {
//					printf("\r\n Publish err: %d\n", err);
//					if (err == -11)
//					{
//
//					}
//				}
//			}
//		//	err = mqtt_publish(client, pub_topic, publish_buffer,strlen(publish_buffer), QOS_0, 0,mqtt_bridge_pub_request_cb,NULL);
//
////			if (err != ERR_OK) {
////				printf("\r\n Publish err_ntt: %d\n", err);
////				if (err == -11)
////				{
//////					MX_LWIP_Init();
////				}
////			}
//
//		} else {
//			/*Create Json and publish to mqtt */
////			memset(publish_buffer, 0, MAX_JSON_LEN);
////			strcat(publish_buffer, "{\"NodeID\":");
////			strcat(publish_buffer, itoa_user(0, 10));
////			strcat(publish_buffer, ",\"FunC\":");
////			strcat(publish_buffer, itoa_user(MB_FUNC_ACK, 10));
////			strcat(publish_buffer, ",\"RegAdrH\":");
////			strcat(publish_buffer,
////					itoa_user(xQueueMbMQtt.RegAdr.i8data[1], 10));
////			strcat(publish_buffer, ",\"RegAdrL\":");
////			strcat(publish_buffer,
////					itoa_user(xQueueMbMQtt.RegAdr.i8data[0], 10));
////			strcat(publish_buffer, ",\"RegDataH\":");
////			strcat(publish_buffer,
////					itoa_user(xQueueMbMQtt.RegData.i8data[1], 10));
////			strcat(publish_buffer, ",\"RegDataL\":");
////			strcat(publish_buffer,
////					itoa_user(xQueueMbMQtt.RegData.i8data[0], 10));
////			strcat(publish_buffer, ",\"PortID\":");
////			strcat(publish_buffer, itoa_user(xQueueMbMQtt.PortID, 10));
////			strcat(publish_buffer, "}");
//////			HAL_UART_Transmit(&huart1, publish_buffer, MAX_JSON_LEN, 1000);
////			err = mqtt_publish(client, pub_topic, publish_buffer,
////					strlen(publish_buffer), QOS_0, 0,
////					mqtt_bridge_pub_request_cb,
////					NULL);
////			if (err != ERR_OK) {
////				mqtt_couter_err++;
////
////				printf("\r\n Publish err: %d\n", err);
////				if (mqtt_couter_err == 10) NVIC_SystemReset();
////			}
////			else
////			{
////				mqtt_couter_err = 0;
////			}
//
//		}
////		vTaskDelay(10);
//
//	}
}
//	how to got mqtt intance??
/*-------------------------------------PROVISION DOWNSTREAM---------------------------------------------------------------------------------------*/
uint8_t mqtt_modbus_thread_down_provision(char *pJsonMQTTBuffer,uint16_t pJsonMQTTBufferLen) {
	/*Parsing json by using clone source :) */
//	int i;
//	int r;
//	jsmn_parser p;
//	jsmntok_t t[JSON_MAX_LEN]; /* We expect no more than JSON_MAX_LEN tokens */
//	jsmn_init(&p);
//	xQueueMbMqtt_t xQueueMbMqtt;
//	r = jsmn_parse(&p, pJsonMQTTBuffer, pJsonMQTTBufferLen, t,sizeof(t) / sizeof(t[0]));
//	if (r < 0) {
//		printf("Failed to parse JSON: %d\n", r);
//		return 1;
//	}
//
//	/* Assume the top-level element is an object */
//	if (r < 1 || t[0].type != JSMN_OBJECT) {
//		printf("Object expected\n");
//		return 1;
//	}
//    dev = 28;
//	/* Loop over all keys of the root object */
//	for (i = 1; i < r; i++) {
//		if (jsoneq(pJsonMQTTBuffer, &t[i], "name") == 0) {
//			/* We may use strndup() to fetch string value */
//			printf("\r\n - name: %.*s\n", t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start);
//			char name[20];
//			strncpy(name, pJsonMQTTBuffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
//			for (uint16_t j = 0; j < 28; j++)
//			{
//				if (strstr(table1[j].c, name) != NULL)
//				{
//					printf("\r\n - name_dev: %s\n",table1[j].deviceName);
//					printf("\r\n device created successfully %s\n");
//				}
//				else
//				{
//					printf("\r\n device not created with %s\n", table1[j].deviceName);
//				}
//			}
//			i++;
//		}
//		else if (jsoneq(pJsonMQTTBuffer, &t[i], "value") == 0) {
//			/* We may additionally check if the value is either "true" or "false" */
//			char value[20];
//			printf("\r\n - value: %.*s\n", t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start);
//			strncpy(value, pJsonMQTTBuffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
//			//i++;
//		}
//	}
//	memset(pJsonMQTTBuffer,"\0",pJsonMQTTBufferLen);
//	fflush(stdin);
//	//xQueueMbMqtt.mutex = 1;  // set mutex for mdtask;
//	BaseType_t Err = pdFALSE;
//	Err = xQueueSend(xQueueDownlinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
//	if (Err == pdPASS) {
//	} else {
//		printf("\r\n Modbus_MQTT Downlink queued: False \r\n");
//	}

}
/*--------------------------------------COMMAND DOWNSTREAM-------------------------------------------------------------------------*/
uint8_t mqtt_modbus_thread_down_command(char *pJsonMQTTBuffer,uint16_t pJsonMQTTBufferLen) {
//	/*Parsing json by using clone source :) */
//		int i;
//		int r;
//		jsmn_parser p;
//		jsmntok_t t[JSON_MAX_LEN]; /* We expect no more than JSON_MAX_LEN tokens */
//		jsmn_init(&p);
//		xQueueMbMqtt_t xQueueMbMqtt;
//		r = jsmn_parse(&p, pJsonMQTTBuffer, pJsonMQTTBufferLen, t,sizeof(t) / sizeof(t[0]));
//		if (r < 0) {
//			printf("Failed to parse JSON: %d\n", r);
//			return 1;
//		}
//
//		/* Assume the top-level element is an object */
//		if (r < 1 || t[0].type != JSMN_OBJECT) {
//			printf("Object expected\n");
//			return 1;
//		}
//	    dev = 28;
//		/* Loop over all keys of the root object */
//		for (i = 1; i < r; i++) {
//			if (jsoneq(pJsonMQTTBuffer, &t[i], "name") == 0) {
//				/* We may use strndup() to fetch string value */
//				printf("\r\n - name: %.*s\n", t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start);
//				char name[20];
//				strncpy(name, pJsonMQTTBuffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
//				for (uint16_t j = 0; j < 28; j++)
//				{
//					if (strstr(table1[j].deviceName, name) != NULL)
//					{
//						printf("\r\n - name_dev: %s\n",table1[j].deviceName);
//						xQueueMbMqtt.NodeID = table1[j].deviceID;
//						xQueueMbMqtt.FunC = table1[j].func;
//						xQueueMbMqtt.RegAdr.i8data[0] = (uint8_t)(table1[j].deviceChannel); // Low Byte
//						xQueueMbMqtt.RegAdr.i8data[1] = (uint8_t)(table1[j].deviceChannel>>8);// High Byte
//						xQueueMbMqtt.PortID = table1[j].channel;
//					}
//				}
//				i++;
//			}
//			else if (jsoneq(pJsonMQTTBuffer, &t[i], "value") == 0) {
//				/* We may additionally check if the value is either "true" or "false" */
//				uint16_t value;
//				char val[20];
//				printf("\r\n - value: %.*s\n", t[i + 1].end - t[i + 1].start,pJsonMQTTBuffer + t[i + 1].start);
//				strncpy(val, pJsonMQTTBuffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
//				printf("\r\nval: %s\r\n",val);
//				if (strstr(val,"true") != NULL)
//					value = 1;
//				else if (strstr(val,"false") != NULL)
//					value = 0;
//				else
//					value = atoi(pJsonMQTTBuffer + t[i + 1].start);
//				xQueueMbMqtt.RegData.i8data[0] = (uint8_t)value;
//				xQueueMbMqtt.RegData.i8data[1] = (uint8_t)(value >> 8);
//				//i++;
//			}
//		}
//		memset(pJsonMQTTBuffer,"\0",pJsonMQTTBufferLen);
//		fflush(stdin);
//		BaseType_t Err = pdFALSE;
//		Err = xQueueSend(xQueueDownlinkHandle, &xQueueMbMqtt,portDEFAULT_WAIT_TIME);
//		if (Err == pdPASS) {
//		} else {
//			printf("\r\n Modbus_MQTT Downlink queued: False \r\n");
//		}

}

