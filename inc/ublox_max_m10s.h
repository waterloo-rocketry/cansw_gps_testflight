#ifndef UBLOX_MAX_M10S_H
#define UBLOX_MAX_M10S_H

#include <stdbool.h>
#include <stdint.h>
#include "rocketlib.h"
#include "stm32h5xx_hal.h"

typedef struct {
    uint32_t itow_ms;      // GPS time of week (ms), (tags which reading this is)
    bool     fix_ok;       // true means position is trustworthy (3D fix + gnssFixOK)
    uint8_t  num_sats;     // # of satellites used
    int32_t  lat_e7;       // latitude ->  degrees*10^7
    int32_t  lon_e7;       // longitude -> degrees*10^7
    int32_t  alt_msl_mm;   // altitude above sea level (mm)
    int32_t  vel_n_mms;    // velocity north (mm/s)
    int32_t  vel_e_mms;    // velocity east (mm/s)
    int32_t  vel_d_mms;    // velocity down (mm/s)
    uint32_t h_acc_mm;     // horizontal accuracy estimate (mm)
} ublox_data_t;

//start receiving, send config, return W_FAILURE if config fails, W_SUCCESS if config succeeds
w_status_t ublox_init(UART_HandleTypeDef *huart);

//reads new bytes from the UART, returns W_SUCCESS if a new message was processed, W_NO_DATA if no new message was processed, or W_FAILURE if an error occurred
w_status_t ublox_process(void);

//returns latest data
w_status_t ublox_get_latest(ublox_data_t *out);

void ublox_rx_event_isr(uint16_t size);
void ublox_error_isr(void);

#endif