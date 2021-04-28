#include "my_mibs.h"
#include "lwip/snmp.h"
#include "lwip/apps/snmp.h"
#include "lwip/apps/snmp_core.h"
#include "lwip/apps/snmp_scalar.h"
#include <string.h>
#include "lwip/apps/snmp_mib2.h"
#include "lwip/apps/snmp_table.h"
#include "lwip/sys.h"

extern char Red1_str[3];
extern char Red2_str[3];
extern char Green1_str[3];
extern char Green2_str[3];
extern char Blue1_str[3];
extern char Blue2_str[3];
extern char White1_str[3];
extern char White2_str[3];
extern float T_avg;
extern uint8_t ColorRGBW[8];


static s16_t get_color_value(struct snmp_node_instance* instance, void* value);
static s16_t get_temperature_value(struct snmp_node_instance* instance,
		void* value);
static s16_t get_Red1(struct snmp_node_instance* instance, void* value);
static snmp_err_t set_Red1(struct snmp_node_instance* instance, u16_t len,
		void *value);

static s16_t get_Green1(struct snmp_node_instance* instance, void* value);
static snmp_err_t set_Green1(struct snmp_node_instance* instance, u16_t len,
		void *value);

static s16_t get_Blue1(struct snmp_node_instance* instance, void* value);
static snmp_err_t set_Blue1(struct snmp_node_instance* instance, u16_t len,
		void *value);

static s16_t get_White1(struct snmp_node_instance* instance, void* value);
static snmp_err_t set_White1(struct snmp_node_instance* instance, u16_t len,
		void *value);

static s16_t get_Red2(struct snmp_node_instance* instance, void* value);
static snmp_err_t set_Red2(struct snmp_node_instance* instance, u16_t len,
		void *value);

static s16_t get_Green2(struct snmp_node_instance* instance, void* value);
static snmp_err_t set_Green2(struct snmp_node_instance* instance, u16_t len,
		void *value);

static s16_t get_Blue2(struct snmp_node_instance* instance, void* value);
static snmp_err_t set_Blue2(struct snmp_node_instance* instance, u16_t len,
		void *value);

static s16_t get_White2(struct snmp_node_instance* instance, void* value);
static snmp_err_t set_White2(struct snmp_node_instance* instance, u16_t len,
		void *value);

static const struct snmp_scalar_node switches_color =
SNMP_SCALAR_CREATE_NODE_READONLY(0, SNMP_ASN1_TYPE_OCTET_STRING,
		get_color_value);

static const struct snmp_scalar_node switches_temperature =
SNMP_SCALAR_CREATE_NODE_READONLY(1, SNMP_ASN1_TYPE_INTEGER,
		get_temperature_value);

static const struct snmp_scalar_node Red1_node =
SNMP_SCALAR_CREATE_NODE(2, SNMP_NODE_INSTANCE_READ_WRITE,
		SNMP_ASN1_TYPE_INTEGER, get_Red1, NULL, set_Red1);

static const struct snmp_scalar_node Green1_node =
SNMP_SCALAR_CREATE_NODE(3, SNMP_NODE_INSTANCE_READ_WRITE,
		SNMP_ASN1_TYPE_INTEGER, get_Green1, NULL, set_Green1);

static const struct snmp_scalar_node Blue1_node =
SNMP_SCALAR_CREATE_NODE(4, SNMP_NODE_INSTANCE_READ_WRITE,
		SNMP_ASN1_TYPE_INTEGER, get_Blue1, NULL, set_Blue1);

static const struct snmp_scalar_node White1_node =
SNMP_SCALAR_CREATE_NODE(5, SNMP_NODE_INSTANCE_READ_WRITE,
		SNMP_ASN1_TYPE_INTEGER, get_White1, NULL, set_White1);

static const struct snmp_scalar_node Red2_node =
SNMP_SCALAR_CREATE_NODE(6, SNMP_NODE_INSTANCE_READ_WRITE,
		SNMP_ASN1_TYPE_INTEGER, get_Red2, NULL, set_Red2);

static const struct snmp_scalar_node Green2_node =
SNMP_SCALAR_CREATE_NODE(7, SNMP_NODE_INSTANCE_READ_WRITE,
		SNMP_ASN1_TYPE_INTEGER, get_Green2, NULL, set_Green2);

static const struct snmp_scalar_node Blue2_node =
SNMP_SCALAR_CREATE_NODE(8, SNMP_NODE_INSTANCE_READ_WRITE,
		SNMP_ASN1_TYPE_INTEGER, get_Blue2, NULL, set_Blue2);

static const struct snmp_scalar_node White2_node =
SNMP_SCALAR_CREATE_NODE(9, SNMP_NODE_INSTANCE_READ_WRITE,
		SNMP_ASN1_TYPE_INTEGER, get_White2, NULL, set_White2);

static const struct snmp_node* const pashnin_nodes[] = {
		&switches_color.node.node, &switches_temperature.node.node,
		&Red1_node.node.node, &Green1_node.node.node, &Blue1_node.node.node,
		&White1_node.node.node, &Red2_node.node.node, &Green2_node.node.node,
		&Blue2_node.node.node, &White2_node.node.node };

static const struct snmp_tree_node pashnin_tree_node =
SNMP_CREATE_TREE_NODE(1, pashnin_nodes);

static const u32_t my_base_oid[] = { 1, 3, 6, 1, 4, 1, 26381, 1 };
const struct snmp_mib pashnin_mib =
SNMP_MIB_CREATE(my_base_oid, &pashnin_tree_node.node);

/*----------------------------------------------------------------------------*/
/* switches value .1.3.6.1.4.1.26381.1.0.0 */
static s16_t get_color_value(struct snmp_node_instance* instance, void* value) {

	uint8_t color_code[24] = { 0 };
	strcat(color_code, Red1_str);
	strcat(color_code, Green1_str);
	strcat(color_code, Blue1_str);
	strcat(color_code, White1_str);
	strcat(color_code, Red2_str);
	strcat(color_code, Green2_str);
	strcat(color_code, Blue2_str);
	strcat(color_code, White2_str);

	const u8_t* var = NULL;
	const s16_t* var_len;
	u16_t result;
	var = color_code;
	var_len = sizeof(color_code);

	/* handle string values (OID 1,4,5 and 6) */
	LWIP_ASSERT("", (value != NULL));
	if (var_len == NULL) {
		result = (s16_t) strlen((const char*) var);
	} else {
		result = var_len;
	}
	MEMCPY(value, var, result);
	return result;
}

/* leds value .1.3.6.1.4.1.26381.1.1.0 */
static s16_t get_temperature_value(struct snmp_node_instance* instance,
		void* value) {

	int *int_ptr = (int*) value;
	*int_ptr = (int) (T_avg * 100);
	return sizeof(*int_ptr);
}

/* leds value .1.3.6.1.4.1.26381.1.2.0 */
static s16_t get_Red1(struct snmp_node_instance* instance, void* value) {

	int *int_ptr = (int*) value;
	*int_ptr = (int) (ColorRGBW[0]);
	return sizeof(*int_ptr);
}
static snmp_err_t set_Red1(struct snmp_node_instance* instance, u16_t len,
		void *value) {
	memset(Red1_str, '\0', sizeof(Red1_str));
	u32_t val = *((u32_t*) value);
	ColorRGBW[0] = (uint8_t) val;
	itoa(ColorRGBW[0], Red1_str, 10);

	if (strlen(Red1_str) == 1) {
		Red1_str[2] = Red1_str[0];
		Red1_str[1] = '0';
		Red1_str[0] = '0';
	}
	if (strlen(Red1_str) == 2) {
		Red1_str[2] = Red1_str[1];
		Red1_str[1] = Red1_str[0];
		Red1_str[0] = '0';
	}
	TIM1->CCR4 = ColorRGBW[0];
	return SNMP_ERR_NOERROR;
}

/* leds value .1.3.6.1.4.1.26381.1.3.0 */
static s16_t get_Green1(struct snmp_node_instance* instance, void* value) {

	int *int_ptr = (int*) value;
	*int_ptr = (int) (ColorRGBW[1]);
	return sizeof(*int_ptr);
}
static snmp_err_t set_Green1(struct snmp_node_instance* instance, u16_t len,
		void *value) {
	memset(Green1_str, '\0', sizeof(Green1_str));
	u32_t val = *((u32_t*) value);
	ColorRGBW[1] = (uint8_t) val;
	itoa(ColorRGBW[1], Green1_str, 10);

	if (strlen(Green1_str) == 1) {
		Green1_str[2] = Green1_str[0];
		Green1_str[1] = '0';
		Green1_str[0] = '0';
	}
	if (strlen(Green1_str) == 2) {
		Green1_str[2] = Green1_str[1];
		Green1_str[1] = Green1_str[0];
		Green1_str[0] = '0';
	}
	TIM1->CCR3 = ColorRGBW[1];
	return SNMP_ERR_NOERROR;
}
/* leds value .1.3.6.1.4.1.26381.1.4.0 */
static s16_t get_Blue1(struct snmp_node_instance* instance, void* value) {

	int *int_ptr = (int*) value;
	*int_ptr = (int) (ColorRGBW[2]);
	return sizeof(*int_ptr);
}
static snmp_err_t set_Blue1(struct snmp_node_instance* instance, u16_t len,
		void *value) {
	memset(Blue1_str, '\0', sizeof(Blue1_str));
	u32_t val = *((u32_t*) value);
	ColorRGBW[2] = (uint8_t) val;
	itoa(ColorRGBW[2], Blue1_str, 10);

	if (strlen(Blue1_str) == 1) {
		Blue1_str[2] = Blue1_str[0];
		Blue1_str[1] = '0';
		Blue1_str[0] = '0';
	}
	if (strlen(Blue1_str) == 2) {
		Blue1_str[2] = Blue1_str[1];
		Blue1_str[1] = Blue1_str[0];
		Blue1_str[0] = '0';
	}
	TIM1->CCR1 = ColorRGBW[2];
	return SNMP_ERR_NOERROR;
}

/* leds value .1.3.6.1.4.1.26381.1.5.0 */
static s16_t get_White1(struct snmp_node_instance* instance, void* value) {

	int *int_ptr = (int*) value;
	*int_ptr = (int) (ColorRGBW[3]);
	return sizeof(*int_ptr);
}
static snmp_err_t set_White1(struct snmp_node_instance* instance, u16_t len,
		void *value) {
	memset(White1_str, '\0', sizeof(White1_str));
	u32_t val = *((u32_t*) value);
	ColorRGBW[3] = (uint8_t) val;
	itoa(ColorRGBW[3], White1_str, 10);

	if (strlen(White1_str) == 1) {
		White1_str[2] = White1_str[0];
		White1_str[1] = '0';
		White1_str[0] = '0';
	}
	if (strlen(White1_str) == 2) {
		White1_str[2] = White1_str[1];
		White1_str[1] = White1_str[0];
		White1_str[0] = '0';
	}
	TIM1->CCR2 = ColorRGBW[3];
	return SNMP_ERR_NOERROR;
}

/* leds value .1.3.6.1.4.1.26381.1.6.0 */
static s16_t get_Red2(struct snmp_node_instance* instance, void* value) {

	int *int_ptr = (int*) value;
	*int_ptr = (int) (ColorRGBW[4]);
	return sizeof(*int_ptr);
}
static snmp_err_t set_Red2(struct snmp_node_instance* instance, u16_t len,
		void *value) {
	memset(Red2_str, '\0', sizeof(Red2_str));
	u32_t val = *((u32_t*) value);
	ColorRGBW[4] = (uint8_t) val;
	itoa(ColorRGBW[4], Red2_str, 10);

	if (strlen(Red2_str) == 1) {
		Red2_str[2] = Red2_str[0];
		Red2_str[1] = '0';
		Red2_str[0] = '0';
	}
	if (strlen(Red2_str) == 2) {
		Red2_str[2] = Red2_str[1];
		Red2_str[1] = Red2_str[0];
		Red2_str[0] = '0';
	}
	TIM4->CCR1 = ColorRGBW[4];
	return SNMP_ERR_NOERROR;
}

/* leds value .1.3.6.1.4.1.26381.1.7.0 */
static s16_t get_Green2(struct snmp_node_instance* instance, void* value) {

	int *int_ptr = (int*) value;
	*int_ptr = (int) (ColorRGBW[5]);
	return sizeof(*int_ptr);
}
static snmp_err_t set_Green2(struct snmp_node_instance* instance, u16_t len,
		void *value) {
	memset(Green2_str, '\0', sizeof(Green2_str));
	u32_t val = *((u32_t*) value);
	ColorRGBW[5] = (uint8_t) val;
	itoa(ColorRGBW[5], Green2_str, 10);

	if (strlen(Green2_str) == 1) {
		Green2_str[2] = Green2_str[0];
		Green2_str[1] = '0';
		Green2_str[0] = '0';
	}
	if (strlen(Green2_str) == 2) {
		Green2_str[2] = Green2_str[1];
		Green2_str[1] = Green2_str[0];
		Green2_str[0] = '0';
	}
	TIM4->CCR2 = ColorRGBW[5];
	return SNMP_ERR_NOERROR;
}
/* leds value .1.3.6.1.4.1.26381.1.8.0 */
static s16_t get_Blue2(struct snmp_node_instance* instance, void* value) {

	int *int_ptr = (int*) value;
	*int_ptr = (int) (ColorRGBW[6]);
	return sizeof(*int_ptr);
}
static snmp_err_t set_Blue2(struct snmp_node_instance* instance, u16_t len,
		void *value) {
	memset(Blue2_str, '\0', sizeof(Blue2_str));
	u32_t val = *((u32_t*) value);
	ColorRGBW[6] = (uint8_t) val;
	itoa(ColorRGBW[6], Blue2_str, 10);

	if (strlen(Blue2_str) == 1) {
		Blue2_str[2] = Blue2_str[0];
		Blue2_str[1] = '0';
		Blue2_str[0] = '0';
	}
	if (strlen(Blue2_str) == 2) {
		Blue2_str[2] = Blue2_str[1];
		Blue2_str[1] = Blue2_str[0];
		Blue2_str[0] = '0';
	}
	TIM4->CCR3 = ColorRGBW[6];
	return SNMP_ERR_NOERROR;
}
/* leds value .1.3.6.1.4.1.26381.1.9.0 */
static s16_t get_White2(struct snmp_node_instance* instance, void* value) {

	int *int_ptr = (int*) value;
	*int_ptr = (int) (ColorRGBW[7]);
	return sizeof(*int_ptr);
}
static snmp_err_t set_White2(struct snmp_node_instance* instance, u16_t len,
		void *value) {
	memset(White2_str, '\0', sizeof(White2_str));
	u32_t val = *((u32_t*) value);
	ColorRGBW[7] = (uint8_t) val;
	itoa(ColorRGBW[7], White2_str, 10);

	if (strlen(White2_str) == 1) {
		White2_str[2] = White2_str[0];
		White2_str[1] = '0';
		White2_str[0] = '0';
	}
	if (strlen(White2_str) == 2) {
		White2_str[2] = White2_str[1];
		White2_str[1] = White2_str[0];
		White2_str[0] = '0';
	}
	TIM4->CCR4 = ColorRGBW[7];
	return SNMP_ERR_NOERROR;
}
