/* gpio.c */

/*
GPIO HAL
*/

#include "gpio.h"

static uint32_t * gpio_instance [] =
{
    (uint32_t *) GPIOA_BASE,
    (uint32_t *) GPIOB_BASE,
    (uint32_t *) GPIOC_BASE,
    (uint32_t *) GPIOD_BASE,
    (uint32_t *) GPIOE_BASE
};

GPIO_STATUS gpio_drv_init (gpio_inst_t gpio_inst, gpio_t * gpio_drv)
{
    gpio_drv = (gpio_t *) gpio_instance[gpio_inst];
}
