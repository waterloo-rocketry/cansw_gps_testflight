#include "ublox_max_m10s.h"

//Configurations as per design doc
#define CFG_UART1OUTPROT_NMEA        0x10740002u
#define CFG_UART1INPROT_NMEA         0x10730002u
#define CFG_MSGOUT_UBX_NAV_PVT_UART1 0x20910007u
#define CFG_NAVSPG_DYNMODEL          0x20110021u
#define CFG_INFMSG_UBX_UART1         0x20920002u

typedef struct { 
	uint32_t key; //bits 15-0: item ID, 23-16: group ID, 27-24: reserved, 31-28: storage size
	uint8_t value; //1 byte config. parameter
} ublox_cfg_item_t;

//Configs as per table in design doc
static const ublox_cfg_item_t ublox_config[] = {
	{CFG_UART1OUTPROT_NMEA, 0},        // NMEA output off
	{CFG_UART1INPROT_NMEA, 0},         // NMEA input off
	{CFG_MSGOUT_UBX_NAV_PVT_UART1, 1}, // NAV-PVT every reading
	{CFG_NAVSPG_DYNMODEL, 8},          // AIR4 (airborne, <4g)
	{CFG_INFMSG_UBX_UART1, 0x03},      // report errors + warnings
};

w_status_t ublox_init(UART_HandleTypeDef *huart) {
	if (!huart) {
		return W_FAILURE; 
	}
	// add later: actually loop over ublox config and send it to the GPS somehow
	(void)ublox_config; //calling table to avoid compiler complaining about "ublox_config" being unused
	// add later: actually receiving
	return W_SUCCESS;
}