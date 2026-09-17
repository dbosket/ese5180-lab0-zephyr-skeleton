#include <zephyr/ztest.h>
#include "bme.h"

ZTEST(bme_test_suite, test_known_vals)
{
    bme280_cal_data cal = {
        .dig_t1 = 28478,
        .dig_t2 = 26952,
        .dig_t3 = 50
    };

    int32_t raw_temp = 519360;
    int32_t result = bme280_cal(raw_temp, &cal);
    zassert_equal(result, 2047,
                  "Expected 20.47 C, got %d", result);
}

ZTEST(bme_test_suite, test_zero_input)
{
    bme280_cal_data cal = {
        .dig_t1 = 28478,
        .dig_t2 = 26952,
        .dig_t3 = 50
    };

    int32_t result = bme280_cal(0, &cal);
    zassert_true(result < 0,
                 "Expected a low temp");
}

ZTEST(bme_test_suite, test_temperature_increases_with_raw_value)
{
    bme280_cal_data cal = {
        .dig_t1 = 28478,
        .dig_t2 = 26952,
        .dig_t3 = 50
    };

    int32_t temp1 = bme280_cal(519328, &cal);
    int32_t temp2 = bme280_cal(519460, &cal);

    zassert_true(temp2 >= temp1,
                 "Expected higher raw val to give higher temp val");
}

ZTEST_SUITE(bme_test_suite, NULL, NULL, NULL, NULL, NULL);