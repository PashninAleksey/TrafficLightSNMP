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

				ColorRGBW[0] = atoi(Red1_str);
				ColorRGBW[1] = atoi(Green1_str);
				ColorRGBW[2] = atoi(Blue1_str);
				ColorRGBW[3] = atoi(White1_str);

				ColorRGBW[4] = atoi(Red2_str);
				ColorRGBW[5] = atoi(Green2_str);
				ColorRGBW[6] = atoi(Blue2_str);
				ColorRGBW[7] = atoi(White2_str);

				if (ColorRGBW[0] > 255) {
					ColorRGBW[0] = 255;
					memset(Red1_str, '\0', sizeof(Red1_str));
					itoa(ColorRGBW[0], Red1_str, 10);
				}


				if (ColorRGBW[1] > 255) {
					ColorRGBW[1] = 255;
					memset(Green1_str, '\0', sizeof(Green1_str));
					itoa(ColorRGBW[1], Green1_str, 10);
				}


				if (ColorRGBW[2] > 255) {
					ColorRGBW[2] = 255;
					memset(Blue1_str, '\0', sizeof(Blue1_str));
					itoa(ColorRGBW[2], Blue1_str, 10);
				}


				if (ColorRGBW[3] > 255) {
					ColorRGBW[3] = 255;
					memset(White1_str, '\0', sizeof(White1_str));
					itoa(ColorRGBW[3], White1_str, 10);
				}


				if (ColorRGBW[4] > 255) {
					ColorRGBW[4] = 255;
					memset(Red2_str, '\0', sizeof(Red2_str));
					itoa(ColorRGBW[4], Red2_str, 10);
				}


				if (ColorRGBW[5] > 255) {
					ColorRGBW[5] = 255;
					memset(Green2_str, '\0', sizeof(Green2_str));
					itoa(ColorRGBW[5], Green2_str, 10);
				}


				if (ColorRGBW[6] > 255) {
					ColorRGBW[6] = 255;
					memset(Blue2_str, '\0', sizeof(Blue2_str));
					itoa(ColorRGBW[6], Blue2_str, 10);
				}


				if (ColorRGBW[7] > 255) {
					ColorRGBW[7] = 255;
					memset(White2_str, '\0', sizeof(White2_str));
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
				uint8_t j = 0;

				for (int i = 0; i < 3; i++) {
					if (Message[j] != '.') {
						ip[0][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				j++;
				for (int i = 0; i < 3; i++) {
					if (Message[j] != '.') {
						ip[1][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				j++;
				for (int i = 0; i < 3; i++) {

					if (Message[j] != '.') {
						ip[2][i] = Message[j];
						j++;
					} else {
						i = 3;
					}

				}
				j++;
				for (int i = 0; i < 3; i++) {

					if (Message[j] != '\0') {
						ip[3][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				IP_ADDRESS[0] = (uint8_t) atoi(ip[0]);
				IP_ADDRESS[1] = (uint8_t) atoi(ip[1]);
				IP_ADDRESS[2] = (uint8_t) atoi(ip[2]);
				IP_ADDRESS[3] = (uint8_t) atoi(ip[3]);
				if (IP_ADDRESS[0] <= 255 && IP_ADDRESS[1] <= 255
						&& IP_ADDRESS[2] <= 255 && IP_ADDRESS[3] <= 255) {

					Set_IP_ADDR(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2],
							IP_ADDRESS[3]);

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
				uint8_t j = 0;

				for (int i = 0; i < 3; i++) {
					if (Message[j] != '.') {
						msk[0][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				j++;
				for (int i = 0; i < 3; i++) {
					if (Message[j] != '.') {
						msk[1][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				j++;
				for (int i = 0; i < 3; i++) {

					if (Message[j] != '.') {
						msk[2][i] = Message[j];
						j++;
					} else {
						i = 3;
					}

				}
				j++;
				for (int i = 0; i < 3; i++) {

					if (Message[j] != '\0') {
						msk[3][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				NETMASK_ADDRESS[0] = (uint8_t) atoi(msk[0]);
				NETMASK_ADDRESS[1] = (uint8_t) atoi(msk[1]);
				NETMASK_ADDRESS[2] = (uint8_t) atoi(msk[2]);
				NETMASK_ADDRESS[3] = (uint8_t) atoi(msk[3]);
				if (NETMASK_ADDRESS[0] <= 255 && NETMASK_ADDRESS[1] <= 255
						&& NETMASK_ADDRESS[2] <= 255
						&& NETMASK_ADDRESS[3] <= 255) {

					Set_MASK_ADDR(NETMASK_ADDRESS[0], NETMASK_ADDRESS[1],
							NETMASK_ADDRESS[2], NETMASK_ADDRESS[3]);

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
				uint8_t j = 0;

				for (int i = 0; i < 3; i++) {
					if (Message[j] != '.') {
						gtw[0][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				j++;
				for (int i = 0; i < 3; i++) {
					if (Message[j] != '.') {
						gtw[1][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				j++;
				for (int i = 0; i < 3; i++) {

					if (Message[j] != '.') {
						gtw[2][i] = Message[j];
						j++;
					} else {
						i = 3;
					}

				}
				j++;
				for (int i = 0; i < 3; i++) {

					if (Message[j] != '\0') {
						gtw[3][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				GATEWAY_ADDRESS[0] = (uint8_t) atoi(gtw[0]);
				GATEWAY_ADDRESS[1] = (uint8_t) atoi(gtw[1]);
				GATEWAY_ADDRESS[2] = (uint8_t) atoi(gtw[2]);
				GATEWAY_ADDRESS[3] = (uint8_t) atoi(gtw[3]);
				if (GATEWAY_ADDRESS[0] <= 255 && GATEWAY_ADDRESS[1] <= 255
						&& GATEWAY_ADDRESS[2] <= 255
						&& GATEWAY_ADDRESS[3] <= 255) {

					Set_GTW_ADDR(GATEWAY_ADDRESS[0], GATEWAY_ADDRESS[1],
							GATEWAY_ADDRESS[2], GATEWAY_ADDRESS[3]);

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
				uint8_t j = 0;

				for (int i = 0; i < 3; i++) {
					if (Message[j] != '.') {
						mac[0][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				j++;
				for (int i = 0; i < 3; i++) {
					if (Message[j] != '.') {
						mac[1][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				j++;
				for (int i = 0; i < 3; i++) {

					if (Message[j] != '.') {
						mac[2][i] = Message[j];
						j++;
					} else {
						i = 3;
					}

				}
				j++;
				for (int i = 0; i < 3; i++) {

					if (Message[j] != '.') {
						mac[3][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}

				j++;
				for (int i = 0; i < 3; i++) {

					if (Message[j] != '.') {
						mac[4][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				j++;
				for (int i = 0; i < 3; i++) {

					if (Message[j] != '\0') {
						mac[5][i] = Message[j];
						j++;
					} else {
						i = 3;
					}
				}
				MACAddr[0] = (uint8_t) atoi(mac[0]);
				MACAddr[1] = (uint8_t) atoi(mac[1]);
				MACAddr[2] = (uint8_t) atoi(mac[2]);
				MACAddr[3] = (uint8_t) atoi(mac[3]);
				MACAddr[4] = (uint8_t) atoi(mac[4]);
				MACAddr[5] = (uint8_t) atoi(mac[5]);
				if (MACAddr[0] <= 255 && MACAddr[1] <= 255 && MACAddr[2] <= 255
						&& MACAddr[3] <= 255 && MACAddr[4] <= 255
						&& MACAddr[5] <= 255) {

					Set_MAC_ADDR(MACAddr[0], MACAddr[1], MACAddr[2], MACAddr[3],
							MACAddr[4], MACAddr[5]);

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

				ColorRGBW[0] = atoi(Red1_str);
				ColorRGBW[1] = atoi(Green1_str);
				ColorRGBW[2] = atoi(Blue1_str);
				ColorRGBW[3] = atoi(White1_str);

				if (ColorRGBW[0] > 255) {
					ColorRGBW[0] = 255;
					memset(Red1_str, '\0', sizeof(Red1_str));
					itoa(ColorRGBW[0], Red1_str, 10);
				}


				if (ColorRGBW[1] > 255) {
					ColorRGBW[1] = 255;
					memset(Green1_str, '\0', sizeof(Green1_str));
					itoa(ColorRGBW[1], Green1_str, 10);
				}


				if (ColorRGBW[2] > 255) {
					ColorRGBW[2] = 255;
					memset(Blue1_str, '\0', sizeof(Blue1_str));
					itoa(ColorRGBW[2], Blue1_str, 10);
				}


				if (ColorRGBW[3] > 255) {
					ColorRGBW[3] = 255;
					memset(White1_str, '\0', sizeof(White1_str));
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

				ColorRGBW[4] = atoi(Red2_str);
				ColorRGBW[5] = atoi(Green2_str);
				ColorRGBW[6] = atoi(Blue2_str);
				ColorRGBW[7] = atoi(White2_str);

				if (ColorRGBW[4] > 255) {
					ColorRGBW[4] = 255;
					memset(Red2_str, '\0', sizeof(Red2_str));
					itoa(ColorRGBW[4], Red2_str, 10);
				}


				if (ColorRGBW[5] > 255) {
					ColorRGBW[5] = 255;
					memset(Green2_str, '\0', sizeof(Green2_str));
					itoa(ColorRGBW[5], Green2_str, 10);
				}


				if (ColorRGBW[6] > 255) {
					ColorRGBW[6] = 255;
					memset(Blue2_str, '\0', sizeof(Blue2_str));
					itoa(ColorRGBW[6], Blue2_str, 10);
				}


				if (ColorRGBW[7] > 255) {
					ColorRGBW[7] = 255;
					memset(White2_str, '\0', sizeof(White2_str));
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
