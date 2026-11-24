#include "ublox_max_m10s.h"
#include "common/common.h"
#include "stm32h5xx_hal.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAX_M10S_SYNC_CHAR_1 (0xB5U)
#define MAX_M10S_SYNC_CHAR_2 (0x62U)

extern UART_HandleTypeDef huart2;

typedef struct {
    uint8_t SYNC_CHAR_1;
    uint8_t SYNC_CHAR_2;

    uint8_t Message_ClassAndID[2];

    /* payload only */
    uint8_t Length[2];

    uint8_t *Payload;

    uint8_t Checksum[2];

} UBX_Packet_t;

static UBX_Packet_t ubx_packet;

static void UBX_AccumulateChecksum (uint8_t *CK_A, uint8_t *CK_B) {
    uint16_t Length = ubx_packet.Length[0] | (ubx_packet.Length[1] << 8);


    *CK_A += ubx_packet.Message_ClassAndID[0];
    *CK_B += *CK_A;

    *CK_A += ubx_packet.Message_ClassAndID[1];
    *CK_B += *CK_A;

    *CK_A += ubx_packet.Length[0];
    *CK_B += *CK_A;

    *CK_A += ubx_packet.Length[1];
    *CK_B += *CK_A;

    for (uint16_t i = 0; i < Length; i++) {
        *CK_A += ubx_packet.Payload[i];
        *CK_B += *CK_A;
    }
}

static void UBX_UpdatePacketChecksum (void) {
    uint8_t CK_A = 0;
    uint8_t CK_B = 0;
    
    UBX_AccumulateChecksum(&CK_A, &CK_B);
    
    ubx_packet.Checksum[0] = CK_A;
    ubx_packet.Checksum[1] = CK_B;
}

// This is a blocking function
static w_status_t MAX_M10S_SendUbxPacket (uint16_t class_id, uint8_t *payload, uint16_t payload_length) {
    uint8_t packet[8 + payload_length];

    ubx_packet.SYNC_CHAR_1 = MAX_M10S_SYNC_CHAR_1;
    ubx_packet.SYNC_CHAR_2 = MAX_M10S_SYNC_CHAR_2;
    ubx_packet.Message_ClassAndID[0] = ((class_id & 0xFF00) >> 8);
    ubx_packet.Message_ClassAndID[1] = (class_id & 0x00FF);
    ubx_packet.Length[0] = (payload_length & 0x00FF);
    ubx_packet.Length[1] = ((payload_length & 0xFF00) >> 8);
    ubx_packet.Payload = payload;
    UBX_UpdatePacketChecksum();

    /* assembly */
    memcpy(packet, &ubx_packet, 6);
    if (payload_length != 0) {
        memcpy(&packet[6], payload, payload_length);
    }
    packet[6 + payload_length] = ubx_packet.Checksum[0];
    packet[7 + payload_length] = ubx_packet.Checksum[1];

    if (HAL_UART_Transmit(&huart2, packet, 8 + payload, 100) != HAL_OK) {
        return W_FAILURE;
    }
    return W_SUCCESS;
}

w_status_t ublox_max_m10s_init(void) {

}

w_status_t ublox_max_m10s_get_data(ublox_max_m10s_data_t* data) {

}

w_status_t ublox_max_m10s_clear_cache(void) {
    
}
