#include "main.h"


char Message[100];

uint8_t ColorRGBW[8];

uint8_t Red1_str[3];
uint8_t Red2_str[3];
uint8_t Green1_str[3];
uint8_t Green2_str[3];
uint8_t Blue1_str[3];
uint8_t Blue2_str[3];
uint8_t White1_str[3];
uint8_t White2_str[3];

extern uint8_t MACAddr[6];
extern uint8_t IP_ADDRESS[4];
extern uint8_t NETMASK_ADDRESS[4];
extern uint8_t GATEWAY_ADDRESS[4];



const char * CLR_All__Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]);
const char * CLR1_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]);
const char * CLR2_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]);
const char * IP_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]);
const char * MSK_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]);
const char * GTW_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]);
const char * MAC_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]);
