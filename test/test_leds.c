#include "unity.h"
#include "leds.h"
#include "mock_errores.h"

static uint16_t puerto_virtual;

void setUp(void) {
    LedsInitDriver(&puerto_virtual);
}

void tearDown(void) {

}

// iniciar el driver y revisar que todos los leds esten apagados
void test_al_iniciar_todos_los_leds_estan_apagados(void) {
    uint16_t puerto_virtual = 0xFFFF;   // como tiene el mismo nombre que la variable global puerto_virtual, la funció la usa sobre la global

    LedsInitDriver(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// prender un led y verificar que no cambia el resto
void test_prender_un_led_y_verificar_que_no_cambia_el_resto(void) {
    LedsTurnOn(3);
    // TEST_ASSERT_BIT_HIGH(puerto_virtual, 2);         // Solo verifica si el led 2 esta encendido
    TEST_ASSERT_EQUAL_HEX16(1 << 2, puerto_virtual);    // Verifica si SOLO el led 2 esta encendido
}

// prender un led y apagarlo cualquiera
void test_prender_un_led_cualquiera_y_apagarlo(void) {
    LedsTurnOn(5);
    LedsTurnOff(5);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// prender mas de un led, apagar uno y verificar que el resto siguen sin cambio
void test_prender_mas_de_un_led_apagar_uno_y_verificar_que_el_resto_sigue_sin_cambios(void) {
    LedsTurnOn(3);
    LedsTurnOn(5);
    LedsTurnOff(3);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, puerto_virtual);
}

// tratar de prender leds fuera de rango y comprobar que se genera un error
void test_tratar_de_prender_leds_fuera_de_rango_y_comprobar_que_se_genera_un_error(void) {
    //RegistrarMensaje_Expect(ALERTA, "LedsTurnOn", 0, "El led no es valido");
    //RegistrarMensaje_IgnoreArg_linea();

    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOn(0);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
    
    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOn(17);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

    // Verifico limite inferior y superior de turnon y turnoff
    // Se recomeindan pruebas cortas -> una para prender y otra para apagar
}

// tratar de apagar leds fuera de rango y comprobar que se genera un error
void test_tratar_de_apagar_leds_fuera_de_rango_y_comprobar_que_se_genera_un_error(void) {
    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOff(0);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
    
    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOff(17);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}