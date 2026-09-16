#include "sum_log.h"

LOG_MODULE_REGISTER(sum_log);


int sum_log(int a, int b){

    int inputs[2] = {a, b};
    int ret = a + b;
    LOG_DBG("%d", ret);
    LOG_INF("%d", ret);
    LOG_WRN("%d", ret);
    LOG_ERR("%d", ret);

    LOG_HEXDUMP_INF(inputs, sizeof(inputs), "Inputs");

    return ret;
}
