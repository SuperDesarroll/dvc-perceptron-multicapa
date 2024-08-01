#ifndef CALCULO_ERROR_H
#define CALCULO_ERROR_H
#include <stdlib.h>
class CalculoError
{
public:
    // Error cuadrático medio (MSE)
    float errorCuadraticoMedio(float salidaDeseada, float salidaObtenida)
    {
        return pow(salidaDeseada - salidaObtenida, 2);
    }

    // Error Diferencia
    float errorDiferencia(float salidaDeseada, float salidaObtenida)
    {        
        float retorno = salidaDeseada - salidaObtenida;        
        return retorno;
    }

    // Error medio (MAE)
    float errorMedioAbsoluto(float salidaDeseada, float salidaObtenida)
    {
        return abs(salidaDeseada - salidaObtenida);
    }

    // Error logarítmico (Cross-Entropy)
    float errorLogaritmico(float salidaDeseada, float salidaObtenida)
    {
        return -salidaDeseada * log(salidaObtenida) - (1 - salidaDeseada) * log(1 - salidaObtenida);
    }
};

#endif // CALCULO_ERROR_H