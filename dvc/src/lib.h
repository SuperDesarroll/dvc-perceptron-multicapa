#include <Arduino.h>
#include <string>
#include "esp_system.h" // Incluir el encabezado para esp_random()

class Library
{
public:
    void Serial_begin()
    {
        Serial.begin(115200);
        Serial.setTimeout(2000);
        Serial.println("Serial ready");
    }

    void randomseed()
    {
        unsigned long seed = esp_random(); // Utiliza el RNG de hardware para obtener la semilla
        Serial.println("Seed: " + String(seed));
        randomSeed(seed); // Inicializa el generador de números aleatorios de Arduino
        srand(seed);      // Inicializa el generador de números aleatorios estándar de C++
    }

    int random(int min, int max)
    {
        return min + (rand() % (max - min + 1));
    }

    void print(std::string str)
    {
        Serial.print(str.c_str());
    }

    void println(std::string str)
    {
        Serial.println(str.c_str());
    }
};