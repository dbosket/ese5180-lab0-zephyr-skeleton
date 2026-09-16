#ifndef SUM_PRINTK_H
#define SUM_PRINTK_H

#include <zephyr/toolchain.h>
#include <zephyr/kernel.h>
#include <stddef.h>
#include <stdarg.h>
#include <inttypes.h>


void sum_printk(int retval);

#endif