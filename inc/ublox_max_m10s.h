#ifndef UBLOX_MAX_M10S_H
#define UBLOX_MAX_M10S_H

#include "common/common.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// @brief Latitude, longitude, and ellipsoidal altitude
typedef struct {
    int32_t latitude;
    int32_t longitude;
    int32_t altitude;
} ublox_max_m10s_position_t;

// @brief NED (North, East, Down) velocity
// @note Down is positive when moving toward the ground (i.e. descending)
typedef struct {
    int32_t velocity_north;
    int32_t velocity_east;
    int32_t velocity_down;
} ublox_max_m10s_velocity_t;

// @brief A snapshot of all the data from the GNSS receiver, taken from a single navigation epoch
// @note All data fields are valid only if is_data_good is true
typedef struct {
    bool is_data_good;
    uint32_t timestamp;
    ublox_max_m10s_position_t position;
    ublox_max_m10s_velocity_t velocity;
} ublox_max_m10s_data_t;

// @brief Initializes communication with the GNSS receiver and applies all the configuration settings to it
// @retval w_status_t status code;
w_status_t ublox_max_m10s_init(void);

// @brief Gets a snapshot of all the receiver data (all fields come from the same navigation epoch)
// @param[out] data Pointer to the ublox_max_m10s_data_t structure that gets updated with the snapshot
// @retval w_status_t status code;
// @note Check the is_data_good field of the returned structure before using any other field
w_status_t ublox_max_m10s_get_data(ublox_max_m10s_data_t* data);

// @brief Clears all the data stored in the current buffer
// @retval w_status_t status code;
w_status_t ublox_max_m10s_clear_cache(void);

// [TODO] Provide a getState and setState function for relevant states

#ifdef __cplusplus
}
#endif

#endif
