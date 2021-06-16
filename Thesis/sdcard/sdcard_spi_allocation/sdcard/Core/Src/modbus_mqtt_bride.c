/* Built-in C library includes ---------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Platform includes --------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "main.h"
#include "json.h"
#include "modbus_mqtt_bridge.h"


/* Network includes----------------------------*/

/* Shared Variables --------------------------*/

/* Private Variables -------------------------*/

static data_t *ptr;

/* Start implementation ---------------------- ---------------------- ---------------------- ---------------------- ----------------------*/

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start
			&& strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}


data_t *parse_device(char *Buffer, uint16_t BufferLen)
{

	int i,r;
	jsmn_parser p;
	jsmntok_t t[JSON_MAX_LEN]; /* We expect no more than JSON_MAX_LEN tokens */
	jsmn_init(&p);
	r = jsmn_parse(&p, Buffer,BufferLen, t,sizeof(t) / sizeof(t[0]));
	for (i = 1; i < r; i++) {
		if (jsoneq(Buffer, &t[i], "PORT") == 0) {
			(ptr)->channel = atoi(Buffer + t[i + 1].start);
			// printf("\nPORT = %d\t",(*ptr)->channel);
			i++;

		} else if (jsoneq(Buffer, &t[i], "ID") == 0) {
			(ptr)->deviceID = atoi(Buffer + t[i + 1].start);
			//printf("ID = %d\t",ptr->deviceID);
			i++;
		} else if (jsoneq(Buffer, &t[i], "FC") == 0) {
			(ptr)->func = atoi(Buffer + t[i + 1].start);
			//printf("FC = %d\t",ptr->func);
			i++;

		} else if (jsoneq(Buffer, &t[i], "CHANNEL") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->deviceChannel = (uint16_t)strtol(temp, NULL, 0);
			//printf("CHANNEL: %d\t",ptr->deviceChannel);
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICETYPE") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->deviceType = temp;
			//printf("DEVICETYPE: %s\t",ptr->deviceType);
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICENAME") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->deviceName = temp;
			//printf("DEVICENAME: %s\t",ptr->deviceName);
			i++;
		} else if (jsoneq(Buffer, &t[i], "CHANNELTITLE") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->channeltitle = temp;
			//printf("CHANNELTITLE: %s\t",ptr->channeltitle);
			i++;
		}else if (jsoneq(Buffer, &t[i], "VALUETYPE") == 0) {
			char temp[20];
			memset(temp,'\0',sizeof(temp));
			strncpy(temp,Buffer + t[i + 1].start, t[i + 1].end - t[i + 1].start);
			(ptr)->valueType= temp;
			//printf("VALUETYPE: %s\t",ptr->valueType);
			i++;
		} else if (jsoneq(Buffer, &t[i], "DEVICESTATUS") == 0) {
			//printf("DEVICESTATUS: %.*s\t", t[i + 1].end - t[i + 1].start,Buffer + t[i + 1].start);
			(ptr)->devicestatus = atoi(Buffer + t[i + 1].start);
			i++;
		}
	}
	return ptr;
}

//void addDevice(data1_t **destination, data1_t *data)
//{
//   (destination)->channel = data->channel;
//   (destination)->deviceID = data->deviceID;
//   (destination)->func = data->func;
//   (destination)->devicestatus = data->devicestatus;
//   (destination)->deviceChannel = data->deviceChannel;
//   (destination)->deviceType = strdup(data->deviceType); // return NULL means fail
//   (destination)->deviceName = strdup(data->deviceName);
//   (destination)->channeltitle = strdup(data->channeltitle);
//   (destination)->valueType = strdup(data->valueType);
//}
