#ifndef ACTIVACION_H
#define ACTIVACION_H

#include <cmath>

class Activacion
{
public:
    // Función de activación lineal
    float lineal(float x)
    {
        return x;
    }

    // Función de activación escalón
    int escalon(float x)
    {
        return (x >= 0) ? 1 : 0;
    }

    float sigmoid(float x)
    {
        return 1.0 / (1.0 + exp(-x));
    }

    float sigmoidDerivada(float x)
    {
        return x * (1.0 - x);
    }
};

#endif // ACTIVACION_H