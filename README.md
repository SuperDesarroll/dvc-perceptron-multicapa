# dvc-perceptron-multicapa
implementación de un perceptrón multicapa (MLP) en un ESP32, una popular plataforma de microcontroladores. El objetivo es utilizar la capacidad de procesamiento del ESP32 para ejecutar modelos de aprendizaje automático en aplicaciones de IoT

# Proyecto de Red Neuronal

Este proyecto implementa una red neuronal simple que se entrena y predice el estado de varios LEDs basándose en el estado de dos botones. El proyecto está dividido en dos partes principales: `cpp/main.cpp` y `dvc/src/main.cpp`.

## cpp/red_neuronal.h
El archivo red_neuronal.h define la clase RedNeuronal, que representa una red neuronal simple con una capa oculta y una capa de salida. La clase incluye métodos para entrenar la red y predecir salidas basadas en entradas dadas. La red neuronal está diseñada para resolver el problema XOR.

## Estructura de la clase RedNeuronal:
## Atributos privados:

* Activacion act: Objeto para funciones de activación.
Library lib: Objeto para operaciones de entrada/salida.
Constantes para el número de entradas, ejemplos, neuronas ocultas y salidas.
* float tasaAprendizaje: Tasa de aprendizaje para el ajuste de pesos.
* const float umbralErrorTotal: Umbral para el error total.
* Matrices para las entradas y salidas deseadas.
* Vectores para las capas de perceptrones y las salidas.

## Métodos públicos:

* RedNeuronal(): Constructor que inicializa las capas de perceptrones.
* void entrenar(): Método para entrenar la red neuronal.
* float predecir(float entrada1, float entrada2): Método para predecir la salida basada en las entradas.
cpp/perceptron.h

El archivo perceptron.h define la clase Perceptron, que representa una neurona individual en la red neuronal. La clase incluye métodos para calcular la salida de la neurona y actualizar sus pesos durante el entrenamiento.

## Estructura de la clase Perceptron:
## Atributos privados:

* std::vector<float> pesos: Vector de pesos de la neurona.
* float bias: Bias de la neurona.
* float tasaAprendizaje: Tasa de aprendizaje para el ajuste de pesos.

## Métodos públicos:

* Perceptron(int numEntradas, float tasaAprendizaje): Constructor que inicializa los pesos y el bias.
* float calcularSalida(const std::vector<float>& entrada): Método para calcular la salida de la neurona.
* void actualizarPesos(const std::vector<float>& entrada, float error): Método para actualizar los pesos y el bias basado en el error.
* float getPeso(int indice): Método para obtener un peso específico.
std::string getLineEq(): Método para obtener la ecuación de la línea representada por la neurona.
cpp/main.cpp

El archivo main.cpp contiene la función principal del programa, que crea una instancia de la clase RedNeuronal, entrena la red y realiza predicciones basadas en entradas dadas.

## Estructura del archivo main.cpp:
## Inclusiones de cabeceras:

stdlib.h: Biblioteca estándar de C (se recomienda usar cmath en su lugar).
lib.h, activacion.h, calculo_error.h, red_neuronal.h: Cabeceras específicas del proyecto.
Función main:

Inicializa una instancia de RedNeuronal.
Llama al método entrenar para entrenar la red.
Realiza predicciones usando el método predecir y muestra los resultados.

## Instrucciones de Uso

Compilación y Ejecución en Entorno de Desarrollo:

## Navega al directorio cpp/ y compila el archivo main.cpp.

Ejecuta el binario generado.


# Ejecución en Microcontrolador:

## Asegúrate de tener PlatformIO instalado.

* Navega al directorio dvc/ y carga el código en tu microcontrolador.
* Dependencias
* PlatformIO
* Biblioteca de Arduino para la comunicación serial


## Notas

Asegúrate de configurar correctamente los pines de los botones y LEDs según tu hardware.
La red neuronal se entrena cada vez que se inicia el programa, lo que puede llevar algún tiempo dependiendo de la complejidad del modelo.


¡Disfruta experimentando con tu red neuronal y controlando los LEDs! ```


## Archivos Principales

### `cpp/main.cpp`

Este archivo contiene el punto de entrada principal del programa. Inicializa la comunicación serial y entrena la red neuronal. Luego, realiza predicciones basadas en las entradas y controla los LEDs en consecuencia.

```cpp
#include "lib.h"
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
```

### `dvc/src/main.cpp`

```cpp
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