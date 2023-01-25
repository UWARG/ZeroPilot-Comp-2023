#ifndef INC_INTERFACE_DATATYPES_HPP_
#define INC_INTERFACE_DATATYPES_HPP_

#include <cstdint>
#include "config.hpp"

/* LOS_Link */
typedef struct LosLinkRx_t{
  uint8_t rssi;
  uint8_t rx_channels[NUM_RX_CHANNELS];
};

/* LOS_Position*/
typedef struct {
    // Longitude and Latitude
    double longitude, latitude; // decimal degrees
    double longitude_speed, latitude_speed; // m/s

    // altitude
    float altitude; // m

    // rate of climb
	float climb_rate; // m/s

    // track & heading
    float track, heading; // degrees

    // air speed
    float air_speed; // m/s

    // ground speed
    float ground_speed; // m/s

    // orientation
    float roll, pitch, yaw; // radians
    float roll_rate, pitch_rate, yaw_rate; // radians/s
    	
} PositionData_t;

typedef struct {
    /* 
     * For sensor fusion mainly, so basing this 
     * off of the struct from sensor fusion
     */

    // gps data
    long double latitude;  // 8 Bytes
    long double longitude; // 8 Bytes
    float utcTime;     // 4 Bytes. Time in seconds since 00:00 (midnight)
    float groundSpeed; // in m/s
    int altitude_gps; // in m
    int16_t heading; // in degrees. Should be between 0-360 at all times, but using integer just in case
    uint8_t numSatellites;    // 1 Byte
    uint8_t fixStatus; //0 = No GPS, 1 = GPS fix, 2 = DGSP Fix, 3 = Estimated/Dead Recoking Fix

    // airspeed data
    double airspeed;

    // imu data
    float magx, magy, magz;
    float accx, accy, accz;
    float gyrx, gyry, gyrz;

    // altimeter data
	float pressure, altitude_alt, temp;

} RawPositionData_t;

#endif /* INC_INTERFACE_DATATYPES_HPP_ */