#ifndef UBLOX_MAX_M10S_H
#define UBLOX_MAX_M10S_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// latitude, longitude, and ellipsoidal altitude
typedef struct {
    int32_t latitude;
    int32_t longitude;
    int32_t altitude;
} ublox_max_m10s_Position;

// NED North, East, and Down velocity
typedef struct {
    int32_t velocityNorth;
    int32_t velocityEast;
    int32_t velocityDown;
} ublox_max_m10s_Velocity;

// @brief A snapshot of all the data from the GNSS receiver, taken from a single navigation epoch
// @note All data fields are valid only if isHealthGood is true
typedef struct {
    bool isHealthGood;
    uint32_t timestamp;
    ublox_max_m10s_Position position;
    ublox_max_m10s_Velocity velocity;
    int32_t groundSpeed;
    int32_t heading;
} ublox_max_m10s_Data;

// @brief Initializes communication with the GNSS receiver and applies all the configuration settings to it
// @retval true if initialization and configuration were successful; false otherwise
bool ublox_max_m10s_init(void);

// @brief Checks if the receiver is in good health
// @retval true if in good health; false otherwise
bool ublox_max_m10s_isHealthGood(void);

// @brief Gets a snapshot of all the receiver data (all fields come from the same navigation epoch)
// @retval A ublox_max_m10s_Data structure containing the data
// @note Check the isHealthGood field of the returned structure before using any other field
ublox_max_m10s_Data ublox_max_m10s_getData(void);

// @brief Gets you the current position (latitude, longitude, and ellipsoidal altitude)
// @param[out] position Pointer to the structure that gets updated with the current position
// @retval true if the position was written to the pointer; false otherwise (the pointed-to memory is left unchanged)
// [TODO] Finalize the scale and unit of lat/long/alt
bool ublox_max_m10s_getPosition(ublox_max_m10s_Position *position);

// @brief Gets the GPS time of week of the navigation epoch
// @param[out] timestamp Pointer to the variable that gets updated with the time, in milliseconds since the start of the GPS week
// @retval true if the timestamp was written to the pointer; false otherwise (the pointed-to memory is left unchanged)
// [TODO] Finalize the scale and unit of timestamp
bool ublox_max_m10s_getTimestamp(uint32_t *timestamp);

// @brief Gets current NED North, East, and Down velocity
// @param[out] velocity Pointer to the structure that gets updated with the current velocity
// @retval true if the velocity was written to the pointer; false otherwise (the pointed-to memory is left unchanged)
// [TODO] Finalize the scale and unit of velocities
bool ublox_max_m10s_getVelocity(ublox_max_m10s_Velocity *velocity);

// @brief Gets current ground speed (2-D)
// @param[out] groundSpeed Pointer to the variable that gets updated with the current ground speed
// @retval true if the ground speed was written to the pointer; false otherwise (the pointed-to memory is left unchanged)
// [TODO] Finalize the scale and unit of velocities
bool ublox_max_m10s_getGroundSpeed(int32_t *groundSpeed);

// @brief Gets current heading of motion (2-D)
// @param[out] heading Pointer to the variable that gets updated with the current heading
// @retval true if the heading was written to the pointer; false otherwise (the pointed-to memory is left unchanged)
// [TODO] Finalize the scale and unit of heading
// [TODO] Look at the difference between "Heading of Motion" and "Heading of Vehicle" before implementing
bool ublox_max_m10s_getHeading(int32_t *heading);

// @brief Clears all the data stored in the current buffer
// @retval true if action performed successfully; false otherwise
bool ublox_max_m10s_clearCache(void);

// [TODO] Provide a getState and setState function for relevant states

#ifdef __cplusplus
}
#endif

#endif
