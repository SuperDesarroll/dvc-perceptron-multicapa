// red_neuronal.h
#ifndef RED_NEURONAL_H
#define RED_NEURONAL_H

#include "perceptron.h"
#include <vector>
#include <iostream>

class RedNeuronal
{
private:
    Activacion act;
    Library lib;
    static const int numEntradas = 2;
    static const int numEjemplos = 4;
    static const int numNeuronasOcultas = 2;
    static const int numSalidas = 1;
    float tasaAprendizaje = 0.1;
    const float umbralErrorTotal = 0.01;

    int entradas[numEjemplos][numEntradas] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}};
    int salidaDeseada[numEjemplos][numSalidas] = {
        {0},
        {1},
        {1},
        {0}}; // XOR

    std::vector<Perceptron> capaOculta;
    std::vector<Perceptron> capaSalida;

    std::vector<float> salidaOculta;
    std::vector<float> salida;

public:
    RedNeuronal()
    {
        for (int i = 0; i < numNeuronasOcultas; i++)
        {
            capaOculta.push_back(Perceptron(numEntradas, tasaAprendizaje));
        }
        for (int i = 0; i < numSalidas; i++)
        {
            capaSalida.push_back(Perceptron(numNeuronasOcultas, tasaAprendizaje));
        }
        salidaOculta.resize(numNeuronasOcultas);
        salida.resize(numSalidas);
    }

    void entrenar()
    {
        for (int epoca = 0; epoca < 10000; epoca++)
        {
            float errorTotal = 0;
            for (int i = 0; i < numEjemplos; i++)
            {
                // Forward pass
                for (int j = 0; j < numNeuronasOcultas; j++)
                {
                    std::vector<float> entrada(entradas[i], entradas[i] + numEntradas);
                    salidaOculta[j] = capaOculta[j].calcularSalida(entrada);
                }
                for (int j = 0; j < numSalidas; j++)
                {
                    salida[j] = capaSalida[j].calcularSalida(salidaOculta);
                }

                // Calcular error y realizar backpropagation
                std::vector<float> errorSalida(numSalidas);
                for (int j = 0; j < numSalidas; j++)
                {
                    errorSalida[j] = salidaDeseada[i][j] - salida[j];
                    errorTotal += errorSalida[j] * errorSalida[j];
                }

                std::vector<float> errorOculta(numNeuronasOcultas);
                for (int j = 0; j < numNeuronasOcultas; j++)
                {
                    errorOculta[j] = 0;
                    for (int k = 0; k < numSalidas; k++)
                    {
                        errorOculta[j] += errorSalida[k] * capaSalida[k].getPeso(j);
                    }
                    errorOculta[j] *= act.sigmoidDerivada(salidaOculta[j]);
                }

                // Actualizar pesos y bias
                for (int j = 0; j < numSalidas; j++)
                {
                    capaSalida[j].actualizarPesos(salidaOculta, errorSalida[j]);
                }
                for (int j = 0; j < numNeuronasOcultas; j++)
                {
                    std::vector<float> entrada(entradas[i], entradas[i] + numEntradas);
                    capaOculta[j].actualizarPesos(entrada, errorOculta[j]);
                }
            }
            // por cada epoca mostramos el error total
            lib.println("Epoca " + std::to_string(epoca) + " Error total: " + std::to_string(errorTotal));
            if (errorTotal < umbralErrorTotal)
                break;
        }
        // al finalizar mostramos las ecuaciones de las lineas de las capas oculta
        for (int j = 0; j < numNeuronasOcultas; j++)
        {
            lib.println("Linea oculta " + std::to_string(j) + ": " + capaOculta[j].getLineEq());
        }
        // al finalizar mostramos las ecuaciones de las lineas de la salida
        for (int j = 0; j < numSalidas; j++)
        {
            lib.println("Linea salida " + std::to_string(j) + ": " + capaSalida[j].getLineEq());
        }
    }

    float predecir(float entrada1, float entrada2)
    {
        std::vector<float> entrada = {entrada1, entrada2};
        for (int j = 0; j < numNeuronasOcultas; j++)
        {
            salidaOculta[j] = capaOculta[j].calcularSalida(entrada);
        }
        for (int j = 0; j < numSalidas; j++)
        {
            salida[j] = capaSalida[j].calcularSalida(salidaOculta);
        }
        lib.println("Prediccion para (" + std::to_string(entrada1) + ", " + std::to_string(entrada2) + ") = " + std::to_string(salida[0]));
        return salida[0];
    }
};

#endif // RED_NEURONAL_H