/************************************************************************************************
Copyright (c) 2025, Lucas Kirschner <kirschnerlucas1@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file    gpio.c
 ** @brief   Implementación de la API de GPIO.
 ** @ingroup gpio
 ** @{ */

/* === Headers files inclusions =============================================================== */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "hal_gpio.h" // Incluye los prototipos de la HAL utilizada

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/** @brief Tipo opaco que representa un GPIO. */
struct gpio_s {
    uint8_t port; /**< Puerto del GPIO */
    uint8_t bit;  /**< Bit del GPIO */
    bool output;  /**< Indica si el GPIO es de salida o entrada */
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

gpio_t gpioCreate(uint8_t port, uint8_t bit) {
    gpio_t self = malloc(sizeof(struct gpio_s));

    if (NULL != self) {
        self->port = port;
        self->bit = bit;
        self->output = false;
    }
    return self;
}

void gpioDestroy(gpio_t self) {
    if (NULL == self)
        return;
    free(self);
}

void gpioSetOutput(gpio_t self, bool output) {
    if (NULL == self)
        return;
    self->output = output;
    hal_gpio_set_direction(self->port, self->bit, output);
}

void gpioSetState(gpio_t self, bool state) {
    if (NULL == self)
        return;
    if (self->output) {
        hal_gpio_set_output(self->port, self->bit, output);
    }
}

bool gpioGetState(gpio_t self) {
    if (NULL == self)
        return;
    return hal_gpio_get_input(self->port, self->bit);
}

/* === End of documentation ==================================================================== */

/** @} end of ingroup gpio */
