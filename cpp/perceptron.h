// perceptron.h
#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <cmath>
#include <cstdlib>

class Perceptron
{
private:
    Activacion act;
    std::vector<float> pesos;
    float bias;
    float tasaAprendizaje;

public:
    Perceptron(int numEntradas, float tasaAprendizaje) : tasaAprendizaje(tasaAprendizaje)
    {
        for (int i = 0; i < numEntradas; i++)
        {
            pesos.push_back(((float)rand() / RAND_MAX) * 2 - 1);
        }
        bias = ((float)rand() / RAND_MAX) * 2 - 1;
    }

    float calcularSalida(const std::vector<float> &entradas)
    {
        float suma = bias;
        for (size_t i = 0; i < entradas.size(); i++)
        {
            suma += entradas[i] * pesos[i];
        }
        return act.sigmoid(suma);
    }

    void actualizarPesos(const std::vector<float> &entradas, float error)
    {
        for (size_t i = 0; i < pesos.size(); i++)
        {
            pesos[i] += tasaAprendizaje * error * entradas[i];
        }
        bias += tasaAprendizaje * error;
    }

    float getPeso(int index) const
    {
        return pesos[index];
    }

    float getBias() const
    {
        return bias;
    }

    // return equation of line as string
    std::string getLineEq()
    {
        std::string eq = "y = ";
        for (size_t i = 0; i < pesos.size(); i++)
        {
            eq += std::to_string(pesos[i]) + "x" + std::to_string(i) + " + ";
        }
        eq += std::to_string(bias);
        return eq;
    }
};

#endif // PERCEPTRON_H