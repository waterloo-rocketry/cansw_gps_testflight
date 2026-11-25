#include "ublox_max_m10s.h"
#include "common/common.h"
#include "stm32h5xx_hal.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
typedef enum { UBX_OK, UBX_NEED_MORE, UBX_BAD_SYNC, UBX_BAD_LEN, UBX_BAD_CHECKSUM } ubx_parse_t;

typedef struct { uint8_t cls, id; uint16_t len; const uint8_t *payload; } ubx_frame_t;

static w_status_t ublox_max_m10s_readubxpacket (uint8_t *payload, uint16_t payload_length){
    
}








w_status_t ublox_max_m10s_init(void){

}
w_status_t ublox_max_m10s_get_data(ublox_max_m10s_data_t* data);{

}
w_status_t ublox_max_m10s_clear_cache(void){

}
