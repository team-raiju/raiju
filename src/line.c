#include <string.h>

#include "line.h"

#include "adc.h"
#include "dma.h"
#include "utils.h"

/****************************************************************
 * Sensor Array Handler
 ****************************************************************/

void line_sensor_array_init(line_sensor_array_t* ls_array) {
    HAL_ADC_Start_DMA(ls_array->hadc, ls_array->dma_buffer, ls_array->dma_buffer_size);
}

void line_sensor_update(line_sensor_array_t* ls_array) {
    memset(ls_array->aux_readings_buffer, 0, ls_array->number_of_sensors * sizeof(uint32_t));

    for (size_t i = 0; i < ls_array->dma_buffer_size; i += ls_array->number_of_sensors) {
        for (size_t j = 0; j < ls_array->number_of_sensors; j++) {
            ls_array->aux_readings_buffer[j] += ls_array->dma_buffer[i + j];
        }
    }

    for (size_t j = 0; j < ls_array->number_of_sensors; j++) {
        ls_array->readings[j] = ls_array->aux_readings_buffer[j] /
                                (ls_array->dma_buffer_size / ls_array->number_of_sensors);
    }

    ls_array->_dma_reading_done = false;
}

void line_sensor_dma_callback(line_sensor_array_t* ls_array) {
    HAL_ADC_Stop_DMA(ls_array->hadc);
    ls_array->_dma_reading_done = true;

    line_sensor_update(ls_array);

    HAL_ADC_Start_DMA(ls_array->hadc, ls_array->dma_buffer, ls_array->dma_buffer_size);
}

uint32_t line_sensor_get_reading(line_sensor_array_t* ls_array, size_t idx) {
    idx = min(idx, ls_array->number_of_sensors);

    return ls_array->readings[idx];
}

/****************************************************************
 * Sensor Array Adapter
 ****************************************************************/

static line_sensor_array_t line_sensors = {
    .hadc = &hadc1,
    .number_of_sensors = 4,

    .dma_buffer = (uint32_t[1024]) { 0 },
    .dma_buffer_size = 1024,

    .readings = (uint32_t[4]) { 0 },
    .aux_readings_buffer = (uint32_t[4]) { 0 },

    ._dma_reading_done = false,
};

void line_sensors_init() {
    MX_DMA_Init();
    MX_ADC1_Init();

    line_sensor_array_init(&line_sensors);
}

uint32_t line_sensor_get(line_sensor_position_t pos) {
    return line_sensors.readings[(int) pos];
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc->Instance == line_sensors.hadc->Instance) {
        line_sensor_dma_callback(&line_sensors);
    }
}

/****************************************************************
 * Sensoring Service
 ****************************************************************/
