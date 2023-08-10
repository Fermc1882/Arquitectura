/* Ejemplo 3LED_bliny para cusos universitarios
 */

#include "mbed.h"
#include <iostream>


// Periodo de parpadeo máximo común divisor - MCD - para los LEDs del LED RGB   
#define BLINKING_UNITS      "ms"
// Falta concatenación de BLINKING_PERIOD y BLINKING_UNITS 
// Periodos de parpadeo adimensionalizados de los LEDs: Tx = LEDx_PERIOD*BLINKING_RATE 
#define LEDR_PERIOD         5       
#define LEDG_PERIOD         7       
#define LEDB_PERIOD         11      
// Objeto para establecer la comunicación serial con el Pc
UnbufferedSerial serial(USBTX, USBRX, 9600);
using namespace std;

int calcularMCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main()
{
    int LedR, LedG, LedB;
    std::cout << "LED R: ";
    std::cin >> LedR;

    std::cout << "LED G: ";
    std::cin >> LedG;

    std::cout << "LED B: ";
    std::cin >> LedB;
    int mcd1 = calcularMCD(LedR, LedG);
    int BLINKING_PERIOD = calcularMCD(mcd1, LedB);
    // Initialise the digital pin LED1 as an output
    DigitalOut ledR(LED1, 1);
    DigitalOut ledG(LED2, 1);
    DigitalOut ledB(LED3, 1);
    // Variable contador - periodos del mcm de los LEDs
    int count = 0;

    while (true) {
        if(count % (LedR/BLINKING_PERIOD) == 0) {
            ledR = !ledR;
            cout << "LedR = " << count*BLINKING_PERIOD << BLINKING_UNITS << endl;
        }
        if(count % (LedG/BLINKING_PERIOD) == 0) {
            ledG = !ledG;
            cout << "LedG = " << count*BLINKING_PERIOD << BLINKING_UNITS << endl;
        }
        if(count % (LedB/BLINKING_PERIOD) == 0) {
            ledB = !ledB;
            cout << "LedB = " << count*BLINKING_PERIOD << BLINKING_UNITS << endl;
        }

        ThisThread::sleep_for(BLINKING_PERIOD);
        count += 1;
    }
}
