#include "main.h"


char Message[100];

uint8_t ColorRGBW[8];

char Red1_str[4];
char Red2_str[4];
char Green1_str[4];
char Green2_str[4];
char Blue1_str[4];
char Blue2_str[4];
char White1_str[4];
char White2_str[4];

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
