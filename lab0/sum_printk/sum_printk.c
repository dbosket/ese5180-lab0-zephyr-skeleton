#include "sum_printk.h"

int sum_printk(int a, int b){
    int retval = a + b;
    printk("The return value is %d\n", retval);
    return retval;
}