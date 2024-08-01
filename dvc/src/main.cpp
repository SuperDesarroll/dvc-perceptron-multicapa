#include "lib.h"
#include "../../cpp/activacion.h"
#include "../../cpp/calculo_error.h"
#include "../../cpp/red_neuronal.h"

#define BUTTON1_PIN 22
#define BUTTON2_PIN 23
#define LED_1 5
#define LED_2 18
#define LED_3 19

Library lib;
RedNeuronal red;

void setup()
{

    lib.Serial_begin();

    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);

    red.entrenar(); 
    lib.println("Iniciando predicciones...");
}

void loop()
{
    lib.println("===================================");
    int button1State = !digitalRead(BUTTON1_PIN);
    int button2State = !digitalRead(BUTTON2_PIN);

    if(button1State == 1)
    {
        digitalWrite(LED_1, HIGH);
        lib.println("Botón 1 presionado");
    }
    else
    {
        digitalWrite(LED_1, LOW);
        lib.println("Botón 1 no presionado");
    }
    if(button2State == 1)
    {
        digitalWrite(LED_2, HIGH);
        lib.println("Botón 2 presionado");
    }
    else
    {        
        digitalWrite(LED_2, LOW);
        lib.println("Botón 2 no presionado");
    }
    // Usa los perceptrones para predecir
    float predictionMulticapa = red.predecir(button1State, button2State);

    // Controla el LED multicapa basado en la predicción multicapa
    if (predictionMulticapa > 0.5)
    {
        digitalWrite(LED_3, HIGH);
        lib.println("LED Multicapa encendido");
    }
    else
    {
        digitalWrite(LED_3, LOW);
        lib.println("LED Multicapa apagado");
    }

    delay(1000);
}