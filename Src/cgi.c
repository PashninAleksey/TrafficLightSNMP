#include "cgi.h"
#include "lwip/apps/httpd.h"
/* if requested to set all colors*/
const char * CLR_All__Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]) {

	if (strcmp(pcParam[0], "CLR_ALL") == 0) {

		memset(Message, '\0', sizeof(Message));
		strcpy(Message, pcValue[0]);
		uint8_t countCLR = 0;

		if (strlen(Message) == 24) {
			for (int i = 0; i < strlen(Message); i++) {
				if (isdigit(Message[i])) {
					countCLR++;
				}
			}
			if (countCLR == 24) {
				memset(Red1_str, '\0', sizeof(Red1_str));
				memset(Red2_str, '\0', sizeof(Red2_str));
				memset(Green1_str, '\0', sizeof(Green1_str));
				memset(Green2_str, '\0', sizeof(Green2_str));
				memset(Blue1_str, '\0', sizeof(Blue1_str));
				memset(Blue2_str, '\0', sizeof(Blue2_str));
				memset(White1_str, '\0', sizeof(White1_str));
				memset(White2_str, '\0', sizeof(White2_str));
				memset(ColorRGBW, '\0', sizeof(ColorRGBW));

				for (int i = 0; i < 3; i++) {
					Red1_str[i] = Message[i];
					Green1_str[i] = Message[i + 3];
					Blue1_str[i] = Message[i + 6];
					White1_str[i] = Message[i + 9];
					Red2_str[i] = Message[i + 12];
					Green2_str[i] = Message[i + 15];
					Blue2_str[i] = Message[i + 18];
					White2_str[i] = Message[i + 21];
				}

				if (atoi(Red1_str) <= 255) {
					ColorRGBW[0] = (uint8_t) atoi(Red1_str);
				} else {
					ColorRGBW[0] = 255;
					itoa(ColorRGBW[0], Red1_str, 10);
				}

				if (atoi(Green1_str) <= 255) {
					ColorRGBW[1] = (uint8_t) atoi(Green1_str);
				} else {
					ColorRGBW[1] = 255;
					itoa(ColorRGBW[1], Green1_str, 10);
				}

				if (atoi(Blue1_str) <= 255) {
					ColorRGBW[2] = (uint8_t) atoi(Blue1_str);
				} else {
					ColorRGBW[2] = 255;
					itoa(ColorRGBW[2], Blue1_str, 10);
				}

				if (atoi(White1_str) <= 255) {
					ColorRGBW[3] = (uint8_t) atoi(White1_str);
				} else {
					ColorRGBW[3] = 255;
					itoa(ColorRGBW[3], White1_str, 10);
				}



				if (atoi(Red2_str) <= 255) {
					ColorRGBW[4] = (uint8_t) atoi(Red2_str);
				} else {
					ColorRGBW[4] = 255;
					itoa(ColorRGBW[4], Red2_str, 10);
				}

				if (atoi(Green2_str) <= 255) {
					ColorRGBW[5] = (uint8_t) atoi(Green2_str);
				} else {
					ColorRGBW[5] = 255;
					itoa(ColorRGBW[5], Green2_str, 10);
				}

				if (atoi(Blue2_str) <= 255) {
					ColorRGBW[6] = (uint8_t) atoi(Blue2_str);
				} else {
					ColorRGBW[6] = 255;
					itoa(ColorRGBW[6], Blue2_str, 10);
				}

				if (atoi(White2_str) <= 255) {
					ColorRGBW[7] = (uint8_t) atoi(White2_str);
				} else {
					ColorRGBW[7] = 255;
					itoa(ColorRGBW[7], White2_str, 10);
				}

				TIM1->CCR1 = ColorRGBW[2];
				TIM1->CCR2 = ColorRGBW[3];
				TIM1->CCR3 = ColorRGBW[1];
				TIM1->CCR4 = ColorRGBW[0];

				TIM4->CCR1 = ColorRGBW[4];
				TIM4->CCR2 = ColorRGBW[5];
				TIM4->CCR3 = ColorRGBW[6];
				TIM4->CCR4 = ColorRGBW[7];

				return "/true.html";

			} else {
				return "/false.html";
			}
		} else if ((strlen(Message) == 1 && Message[0] == '?')
				|| (strlen(Message) == 3 && Message[0] == '%'
						&& Message[1] == '3' && Message[2] == 'F')) {
			return "/color_answer.shtml";
		} else {
			return "/false.html";
		}
	} else {
		return "/false.html";
	}
}
/* if requested to set IP-address*/
const char * IP_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]) {
	uint8_t count_ip = 0;
	uint8_t j = 0;
	memset(Message, '\0', sizeof(Message));
	strcpy(Message, pcValue[0]);
	char ip[4][4] = { '\0' };
	if (strcmp(pcParam[0], "IPset") == 0) {
		strcpy(Message, pcValue[0]);
		if (strlen(Message) <= 15 && strlen(Message) >= 7) {
			for (int i = 0; i < strlen(Message); i++) {
				if (isdigit(Message[i]) || strcmp(Message[i], '.') == 0) {
					count_ip++;
				}
			}
			if (count_ip == strlen(Message)) {
				j = 0;
				for (int k = 0; k < 4; k++) {
					for (int i = 0; i < 3; i++) {
						if (Message[j] != '.') {
							ip[k][i] = Message[j];
							j++;
						} else {
							i = 3;
						}
					}
					j++;
				}
				if (atoi(ip[0]) <= 255 && atoi(ip[1]) <= 255
						&& atoi(ip[2]) <= 255 && atoi(ip[3]) <= 255) {
					IP_ADDRESS[0] = (uint8_t) atoi(ip[0]);
					IP_ADDRESS[1] = (uint8_t) atoi(ip[1]);
					IP_ADDRESS[2] = (uint8_t) atoi(ip[2]);
					IP_ADDRESS[3] = (uint8_t) atoi(ip[3]);

					Set_IP_ADDR(IP_ADDRESS);

					NVIC_SystemReset();
				}
			}
		}
	}
	return "/index.shtml";
}

/* if requested to set MASK*/
const char * MSK_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]) {
	uint8_t count_msk = 0;
	uint8_t j = 0;
	memset(Message, '\0', sizeof(Message));
	strcpy(Message, pcValue[0]);
	char msk[4][4] = { '\0' };
	if (strcmp(pcParam[0], "MSKset") == 0) {
		strcpy(Message, pcValue[0]);
		if (strlen(Message) <= 15 && strlen(Message) >= 7) {
			for (int i = 0; i < strlen(Message); i++) {
				if (isdigit(Message[i]) || strcmp(Message[i], '.') == 0) {
					count_msk++;
				}
			}
			if (count_msk == strlen(Message)) {
				j = 0;
				for (int k = 0; k < 4; k++) {
					for (int i = 0; i < 3; i++) {
						if (Message[j] != '.') {
							msk[k][i] = Message[j];
							j++;
						} else {
							i = 3;
						}
					}
					j++;
				}
				if (atoi(msk[0]) <= 255 && atoi(msk[1]) <= 255
						&& atoi(msk[2]) <= 255 && atoi(msk[3]) <= 255) {

					NETMASK_ADDRESS[0] = (uint8_t) atoi(msk[0]);
					NETMASK_ADDRESS[1] = (uint8_t) atoi(msk[1]);
					NETMASK_ADDRESS[2] = (uint8_t) atoi(msk[2]);
					NETMASK_ADDRESS[3] = (uint8_t) atoi(msk[3]);

					Set_MASK_ADDR(NETMASK_ADDRESS);

					NVIC_SystemReset();
				}
			}
		}
	}
	return "/index.shtml";
}
/* if requested to set Gateway*/
const char * GTW_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]) {
	uint8_t count_gtw = 0;
	uint8_t j = 0;
	memset(Message, '\0', sizeof(Message));
	strcpy(Message, pcValue[0]);
	char gtw[4][4] = { '\0' };
	if (strcmp(pcParam[0], "GTWset") == 0) {
		strcpy(Message, pcValue[0]);
		if (strlen(Message) <= 15 && strlen(Message) >= 7) {
			for (int i = 0; i < strlen(Message); i++) {
				if (isdigit(Message[i]) || strcmp(Message[i], '.') == 0) {
					count_gtw++;
				}
			}
			if (count_gtw == strlen(Message)) {

				for (int k = 0; k < 4; k++) {
					for (int i = 0; i < 3; i++) {
						if (Message[j] != '.') {
							gtw[k][i] = Message[j];
							j++;
						} else {
							i = 3;
						}
					}
					j++;
				}
				if (atoi(gtw[0]) <= 255 && atoi(gtw[1]) <= 255
						&& atoi(gtw[2]) <= 255 && atoi(gtw[3]) <= 255) {
					GATEWAY_ADDRESS[0] = (uint8_t) atoi(gtw[0]);
					GATEWAY_ADDRESS[1] = (uint8_t) atoi(gtw[1]);
					GATEWAY_ADDRESS[2] = (uint8_t) atoi(gtw[2]);
					GATEWAY_ADDRESS[3] = (uint8_t) atoi(gtw[3]);

					Set_GTW_ADDR(GATEWAY_ADDRESS);

					NVIC_SystemReset();
				}
			}
		}
	}
	return "/index.shtml";
}
/* if requested to set MACAddress*/
const char * MAC_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[]) {
	uint8_t count_mac = 0;
	uint8_t j = 0;
	memset(Message, '\0', sizeof(Message));
	strcpy(Message, pcValue[0]);
	char mac[6][4] = { '\0' };
	if (strcmp(pcParam[0], "MACset") == 0) {
		strcpy(Message, pcValue[0]);
		if (strlen(Message) <= 15 && strlen(Message) >= 7) {
			for (int i = 0; i < strlen(Message); i++) {
				if (isdigit(Message[i]) || strcmp(Message[i], '.') == 0) {
					count_mac++;
				}
			}
			if (count_mac == strlen(Message)) {
				j = 0;
				for (int k = 0; k < 6; k++) {
					for (int i = 0; i < 3; i++) {
						if (Message[j] != '.') {
							mac[k][i] = Message[j];
							j++;
						} else {
							i = 3;
						}
					}
					j++;
				}
				if (atoi(mac[0]) <= 255 && atoi(mac[1]) <= 255
						&& atoi(mac[2]) <= 255 && atoi(mac[3]) <= 255
						&& atoi(mac[4]) <= 255 && atoi(mac[5]) <= 255) {
					MACAddr[0] = (uint8_t) atoi(mac[0]);
					MACAddr[1] = (uint8_t) atoi(mac[1]);
					MACAddr[2] = (uint8_t) atoi(mac[2]);
					MACAddr[3] = (uint8_t) atoi(mac[3]);
					MACAddr[4] = (uint8_t) atoi(mac[4]);
					MACAddr[5] = (uint8_t) atoi(mac[5]);

					Set_MAC_ADDR(MACAddr);

					NVIC_SystemReset();
				}
			}
		}
	}
	return "/index.shtml";
}
/* if there is a request to set the colors for the first traffic light*/
const char * CLR1_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[])

{
	if (strcmp(pcParam[0], "CLR1") == 0) {
		memset(Message, '\0', sizeof(Message));
		strcpy(Message, pcValue[0]);
		uint8_t countCLR = 0;
		if (strlen(Message) == 12) {
			for (int i = 0; i < strlen(Message); i++) {
				if (isdigit(Message[i])) {
					countCLR++;
				}
			}
			if (countCLR == 12) {
				memset(Red1_str, '\0', sizeof(Red1_str));
				memset(Green1_str, '\0', sizeof(Green1_str));
				memset(Blue1_str, '\0', sizeof(Blue1_str));
				memset(White1_str, '\0', sizeof(White1_str));

				for (int i = 0; i < 3; i++) {
					Red1_str[i] = Message[i];
					Green1_str[i] = Message[i + 3];
					Blue1_str[i] = Message[i + 6];
					White1_str[i] = Message[i + 9];
				}

				if (atoi(Red1_str) <= 255) {
					ColorRGBW[0] = (uint8_t) atoi(Red1_str);
				} else {
					ColorRGBW[0] = 255;
					itoa(ColorRGBW[0], Red1_str, 10);
				}

				if (atoi(Green1_str) <= 255) {
					ColorRGBW[1] = (uint8_t) atoi(Green1_str);
				} else {
					ColorRGBW[1] = 255;
					itoa(ColorRGBW[1], Green1_str, 10);
				}

				if (atoi(Blue1_str) <= 255) {
					ColorRGBW[2] = (uint8_t) atoi(Blue1_str);
				} else {
					ColorRGBW[2] = 255;
					itoa(ColorRGBW[2], Blue1_str, 10);
				}

				if (atoi(White1_str) <= 255) {
					ColorRGBW[3] = (uint8_t) atoi(White1_str);
				} else {
					ColorRGBW[3] = 255;
					itoa(ColorRGBW[3], White1_str, 10);
				}

				TIM1->CCR1 = ColorRGBW[2];
				TIM1->CCR2 = ColorRGBW[3];
				TIM1->CCR3 = ColorRGBW[1];
				TIM1->CCR4 = ColorRGBW[0];

			}

		}
		return "/index.shtml";

	} else {
		return "/false.html";
	}

}
/* if there is a request to set the colors for the second traffic light*/
const char * CLR2_Handler(int iIndex, int iNumParams, char *pcParam[],
		char *pcValue[])

{

	if (strcmp(pcParam[0], "CLR2") == 0) {
		memset(Message, '\0', sizeof(Message));
		strcpy(Message, pcValue[0]);
		uint8_t countCLR = 0;
		if (strlen(Message) == 12) {
			for (int i = 0; i < strlen(Message); i++) {
				if (isdigit(Message[i])) {
					countCLR++;
				}
			}
			if (countCLR == 12) {
				memset(Red2_str, '\0', sizeof(Red2_str));
				memset(Green2_str, '\0', sizeof(Green2_str));
				memset(Blue2_str, '\0', sizeof(Blue2_str));
				memset(White2_str, '\0', sizeof(White2_str));

				for (int i = 0; i < 3; i++) {
					Red2_str[i] = Message[i];
					Green2_str[i] = Message[i + 3];
					Blue2_str[i] = Message[i + 6];
					White2_str[i] = Message[i + 9];
				}

				if (atoi(Red2_str) <= 255) {
					ColorRGBW[4] = (uint8_t) atoi(Red2_str);
				} else {
					ColorRGBW[4] = 255;
					itoa(ColorRGBW[4], Red2_str, 10);
				}

				if (atoi(Green2_str) <= 255) {
					ColorRGBW[5] = (uint8_t) atoi(Green2_str);
				} else {
					ColorRGBW[5] = 255;
					itoa(ColorRGBW[5], Green2_str, 10);
				}

				if (atoi(Blue2_str) <= 255) {
					ColorRGBW[6] = (uint8_t) atoi(Blue2_str);
				} else {
					ColorRGBW[6] = 255;
					itoa(ColorRGBW[6], Blue2_str, 10);
				}

				if (atoi(White2_str) <= 255) {
					ColorRGBW[7] = (uint8_t) atoi(White2_str);
				} else {
					ColorRGBW[7] = 255;
					itoa(ColorRGBW[7], White2_str, 10);
				}

				TIM4->CCR1 = ColorRGBW[4];
				TIM4->CCR2 = ColorRGBW[5];
				TIM4->CCR3 = ColorRGBW[6];
				TIM4->CCR4 = ColorRGBW[7];

			}

		}
		return "/index.shtml";

	} else {
		return "/false.html";
	}
}

const tCGI CLR_All_CGI = { "/CLR_All_CGI.cgi", CLR_All__Handler };
const tCGI CLR1_CGI = { "/CLR1.cgi", CLR1_Handler };
const tCGI CLR2_CGI = { "/CLR2.cgi", CLR2_Handler };
const tCGI IP_CGI = { "/IP.cgi", IP_Handler };
const tCGI MAC_CGI = { "/MAC.cgi", MAC_Handler };
const tCGI MSK_CGI = { "/MSK.cgi", MSK_Handler };
const tCGI GTW_CGI = { "/GTW.cgi", GTW_Handler };

tCGI CGI_TAB[7];
