#include <stdint.h>
#include "errores.h"

void LedsInitDriver(uint16_t *puerto_virtual);
void LedsTurnOn( int led);   // Usando int me aseguro que el procesador va a hacer la operación lo más rápido posible. Recomendable en los casos en que no haya problemas de rango
void LedsTurnOff(int led);