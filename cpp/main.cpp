#include <stdlib.h> // Asegúrate de incluir cmath en lugar de stdlib.h o math.h

#include "lib.h"
#include "activacion.h"
#include "calculo_error.h"
#include "red_neuronal.h"

int main(int argc, char const *argv[])
{
    Library lib;
    lib.Serial_begin();
    RedNeuronal red;

    red.entrenar();

    int entradas[4][2] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}};

    lib.println("Iniciando predicciones...");
    for (int i = 0; i < 4; i++)
    {
        int button1State = entradas[i][0];
        int button2State = entradas[i][1];
        lib.println("===================================");
        // Usa los perceptrones para predecir
        float predictionMulticapa = red.predecir(button1State, button2State);
        lib.println("");
        // Controla el LED multicapa basado en la predicción multicapa
        if (predictionMulticapa > 0.5)
        {
            lib.println("LED Multicapa encendido");
        }
        else
        {
            lib.println("LED Multicapa apagado");
        }
    }

    return 0;
}
