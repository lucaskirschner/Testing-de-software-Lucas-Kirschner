#include "leds.h"
#include "errores.h"
#include <stdbool.h>

#define ALL_LED_OFF         0x0000
#define FIRST_BIT           1
#define LED_TO_BIT_OFFSET   1

static uint16_t * puerto;

static uint16_t LedToMask(int led) {
    return FIRST_BIT << (led - LED_TO_BIT_OFFSET);
}

static bool IsLedValid(int led) {
    bool result = led >= 1 && led <= 16;
    if(!result) {
        Alerta("El led no es valido");
    }

    return result;
}

void LedsInitDriver(uint16_t *puerto_virtual){
    puerto = puerto_virtual;
    // *puerto = ALL_LED_OFF; // Apagar todos los LEDs al iniciar
    LedsTurnOffAll();
}

void LedsTurnOn(int led){
    if (!IsLedValid(led)) {
        return;
    }

    *puerto |= LedToMask(led);
}

void LedsTurnOff(int led){

    if (!IsLedValid(led)) {
        return;
    }
    
    *puerto &= ~LedToMask(led);
}

void LedsTurnOnAll(void){
    *puerto = ~ALL_LED_OFF;
}

void LedsTurnOffAll(void){
    *puerto = ALL_LED_OFF;
}

bool LedsIsOn (int led){

    if (!IsLedValid(led)) {
        return false;
    }

    return ((*puerto & LedToMask(led)) != 0);
}

bool LedsIsOff(int led){
    if (!IsLedValid(led)) {
        return false;
    }

    return ((*puerto & LedToMask(led)) == 0);
}