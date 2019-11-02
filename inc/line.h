/**
 * @file distance.h
 *
 * @brief Line sensors
 *
 * @author Daniel Nery <danielnso97@gmail.com>
 */

#if !defined(__LINE_H__)
#define __LINE_H__

#include <stdint.h>
#include <stdbool.h>

#include "adc.h"

typedef struct line_sensor_array {
    ADC_HandleTypeDef* hadc;
    size_t             number_of_sensors;

    uint32_t*          dma_buffer;
    size_t             dma_buffer_size;

    uint32_t*          readings;
    uint32_t*          aux_readings_buffer;

    bool               _dma_reading_done;
} line_sensor_array_t;

void line_sensor_array_init(line_sensor_array_t* ls_array);

void line_sensor_update(line_sensor_array_t* ls_array);

void line_sensor_dma_callback(line_sensor_array_t* ls_array);

uint32_t line_sensor_get_reading(line_sensor_array_t* ls_array, size_t idx);

///////////////////////////////

typedef enum {
    FRONT_RIGHT = 1,
    FRONT_LEFT = 2,
    REAR_RIGHT = 0,
    REAR_LEFT = 3,
} line_sensor_position_t;

void line_sensors_init();

uint32_t line_sensor_get(line_sensor_position_t pos);

#endif // __LINE_H__
