
#ifndef BME_H
#define BME_H

#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include <stdint.h>

#define BME5180_NODE DT_ALIAS(bme5180)

#define BME280_CTRL_MEAS  0xF4
#define BME280_TEMP_MSB   0xFA
#define BME280_ID         0xD0
#define BME280_CHIP_ID    0x60
#define BME280_CAL_IB00   0x88

typedef struct bme280_cal_data {
    uint16_t dig_t1;
    int16_t dig_t2;
    int16_t dig_t3;
} bme280_cal_data;

int bme280_config(bme280_cal_data *cal);
int32_t bme280_read(void);

static inline int32_t bme280_cal(int32_t raw_temp, bme280_cal_data *cal){
    int32_t var1;
    int32_t var2;
    int32_t t_fine;

    var1 = ((((raw_temp >> 3) - ((int32_t)cal->dig_t1 << 1))) * ((int32_t)cal->dig_t2)) >> 11;

    var2 = (((((raw_temp >> 4) - ((int32_t)cal->dig_t1)) * ((raw_temp >> 4) - 
            ((int32_t)cal->dig_t1))) >> 12) * ((int32_t)cal->dig_t3)) >> 14;
    t_fine = var1 + var2;
    return ((t_fine * 5 + 128) >> 8);
}
#endif