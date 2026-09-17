#include "bme.h"


static const struct i2c_dt_spec bme =
    I2C_DT_SPEC_GET(BME5180_NODE);

int bme280_config(bme280_cal_data *cal){
    int ret;

    if (!device_is_ready(bme.bus)) {
        printk("BME280 I2C bus is not ready\n");
        return -1;
    }

    // Verify i2c Func
    uint8_t reg = BME280_ID;
    uint8_t id = 0xFF;
    ret = i2c_write_read_dt(&bme, &reg, 1, &id, 1);
    if (ret != 0) {
		printk("Failed to read ID, ret = %d\n", ret);
		return ret;
	}
    printk("BME280 chip ID: 0x%02x\n", id);

    if (id != BME280_CHIP_ID) {
        printk("Invalid BME280 chip ID: 0x%02x\n", id);
        return -1;
    }

    uint8_t cal_vals[6];
    ret = i2c_burst_read_dt(&bme, BME280_CAL_IB00, cal_vals, sizeof(cal_vals));
    if (ret != 0) {
		printk("Failed to read register %x \n", BME280_CAL_IB00);
		return ret;
	}

    cal->dig_t1 = ((uint16_t)cal_vals[1]) << 8 | cal_vals[0];
	cal->dig_t2 = ((uint16_t)cal_vals[3]) << 8 | cal_vals[2];
	cal->dig_t3 = ((uint16_t)cal_vals[5]) << 8 | cal_vals[4];

    uint8_t sensor_config[2] = { BME280_CTRL_MEAS, 0x27 };

    ret = i2c_write_dt(&bme, sensor_config, sizeof(sensor_config));
    if (ret != 0) {
        printk("Failed to write SENSOR CONFIGURATION\n");
        return ret;
    }
    return 0;
}

int32_t bme280_read(void){
    uint8_t temp_data[3];

    int ret = i2c_burst_read_dt(&bme, BME280_TEMP_MSB, temp_data, sizeof(temp_data));
    if (ret != 0) {
        printk("Failed to read BME280 temperature\n");
        return -1;
    }
    int32_t raw_temp = ((int32_t)temp_data[0] << 12) |
                        ((int32_t)temp_data[1] << 4) |
                        (((int32_t)temp_data[2] >> 4) & 0x0F);
    return raw_temp;
}
