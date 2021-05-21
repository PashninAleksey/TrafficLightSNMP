#include "ssi.h"
#include "cgi.h"

extern uint8_t Red1_str[3];
extern uint8_t Red2_str[3];
extern uint8_t Green1_str[3];
extern uint8_t Green2_str[3];
extern uint8_t Blue1_str[3];
extern uint8_t Blue2_str[3];
extern uint8_t White1_str[3];
extern uint8_t White2_str[3];

extern uint8_t MACAddr[6];
extern uint8_t IP_ADDRESS[4];
extern uint8_t NETMASK_ADDRESS[4];
extern uint8_t GATEWAY_ADDRESS[4];

char const* TAGCHAR[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "m", "k",
		"n", "s" };
char const** TAGS = TAGCHAR;

//board temperature
extern float T_avg;
uint16_t SSI_Handler(int iIndex, char *pcInsert, int iInsertLen) {

	if (iIndex == 0) {
		/*tag to show IPAddress */
		memset(pcInsert, '\0', strlen(pcInsert));
		sprintf(pcInsert, "%d.%d.%d.%d", IP_ADDRESS[0], IP_ADDRESS[1],
				IP_ADDRESS[2], IP_ADDRESS[3]);
		return strlen(pcInsert);
	}
	if (iIndex == 1) {
		/*tag to show temperature */
		memset(pcInsert, '\0', strlen(pcInsert));
		sprintf(pcInsert, "%d.%02d", (int) T_avg,
				(uint16_t) ((T_avg - (uint32_t)T_avg) * 100));
		return strlen(pcInsert);
	}

	if (iIndex == 2) {
		/*tag to show Red color of the first traffic light  */
		memset(pcInsert, '\0', strlen(pcInsert));
		strcat(pcInsert, Red1_str);
		return strlen(pcInsert);
	}
	if (iIndex == 3) {
		/*tag to show Green color of the first traffic light  */
		memset(pcInsert, '\0', strlen(pcInsert));
		strcat(pcInsert, Green1_str);
		return strlen(pcInsert);
	}
	if (iIndex == 4) {
		/*tag to show Blue color of the first traffic light  */
		memset(pcInsert, '\0', strlen(pcInsert));
		strcat(pcInsert, Blue1_str);
		return strlen(pcInsert);
	}
	if (iIndex == 5) {
		/*tag to show White color of the first traffic light  */
		memset(pcInsert, '\0', strlen(pcInsert));
		strcat(pcInsert, White1_str);
		return strlen(pcInsert);
	}
	if (iIndex == 6) {
		/*tag to show Red color of the second traffic light  */
		memset(pcInsert, '\0', strlen(pcInsert));
		strcat(pcInsert, Red2_str);
		return strlen(pcInsert);
	}
	if (iIndex == 7) {
		/*tag to show Green color of the second traffic light  */
		memset(pcInsert, '\0', strlen(pcInsert));
		strcat(pcInsert, Green2_str);
		return strlen(pcInsert);
	}
	if (iIndex == 8) {
		/*tag to show Blue color of the second traffic light  */
		memset(pcInsert, '\0', strlen(pcInsert));
		strcat(pcInsert, Blue2_str);
		return strlen(pcInsert);
	}
	if (iIndex == 9) {
		/*tag to show White color of the second traffic light  */

		memset(pcInsert, '\0', strlen(pcInsert));
		strcat(pcInsert, White2_str);
		return strlen(pcInsert);
	}

	if (iIndex == 10) {
		/*tag to show MACAddress */
		memset(pcInsert, '\0', strlen(pcInsert));
		sprintf(pcInsert, "%d.%d.%d.%d.%d.%d", MACAddr[0], MACAddr[1],
				MACAddr[2], MACAddr[3], MACAddr[4], MACAddr[5]);

		return strlen(pcInsert);
	}

	if (iIndex == 11) {
		/*tag to show MASK */
		memset(pcInsert, '\0', strlen(pcInsert));
		sprintf(pcInsert, "%d.%d.%d.%d", NETMASK_ADDRESS[0], NETMASK_ADDRESS[1],
				NETMASK_ADDRESS[2], NETMASK_ADDRESS[3]);
		return strlen(pcInsert);
	}
	if (iIndex == 12) {
		/*tag to show GATEWAY */
		memset(pcInsert, '\0', strlen(pcInsert));
		sprintf(pcInsert, "%d.%d.%d.%d", GATEWAY_ADDRESS[0], GATEWAY_ADDRESS[1],
				GATEWAY_ADDRESS[2], GATEWAY_ADDRESS[3]);
		return strlen(pcInsert);
	}

	return 0;

}
