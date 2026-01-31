// SumaArreglos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Configurar semilla para números aleatorios
    srand(time(NULL));

    // Tamaño del arreglo (máximo 1000)
    const int N = 1000;

    // Declarar los arreglos
    int arreglo1[N];
    int arreglo2[N];
    int arregloResultado[N];

    cout << "=== SUMA DE ARREGLOS CON PROGRAMACION PARALELA (OpenMP) ===" << endl;
    cout << "Tamaño de los arreglos: " << N << " elementos" << endl << endl;

    // Inicializar arreglos con valores aleatorios (0-99)
    cout << "Inicializando arreglos con valores aleatorios..." << endl;
    for (int i = 0; i < N; i++) {
        arreglo1[i] = rand() % 100;
        arreglo2[i] = rand() % 100;
    }

    // Medir tiempo de inicio
    double inicio = omp_get_wtime();

    // Suma paralela usando OpenMP
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        arregloResultado[i] = arreglo1[i] + arreglo2[i];
    }

    // Medir tiempo final
    double fin = omp_get_wtime();
    double tiempo_paralelo = fin - inicio;

    cout << "Suma paralela completada!" << endl;
    cout << "Tiempo de ejecucion (paralelo): " << tiempo_paralelo << " segundos" << endl << endl;

    // Mostrar información de hilos
#pragma omp parallel
    {
#pragma omp master
        {
            cout << "Numero de hilos utilizados: " << omp_get_num_threads() << endl << endl;
        }
    }

    // Imprimir los primeros 10 elementos para verificar
    cout << "=== VERIFICACION (primeros 10 elementos) ===" << endl;
    cout << "Indice\tArreglo1\tArreglo2\tResultado" << endl;
    cout << "------\t--------\t--------\t---------" << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << "\t" << arreglo1[i] << "\t\t"
            << arreglo2[i] << "\t\t" << arregloResultado[i] << endl;
    }

    cout << endl << "=== VERIFICACION (ultimos 10 elementos) ===" << endl;
    cout << "Indice\tArreglo1\tArreglo2\tResultado" << endl;
    cout << "------\t--------\t--------\t---------" << endl;
    for (int i = N - 10; i < N; i++) {
        cout << i << "\t" << arreglo1[i] << "\t\t"
            << arreglo2[i] << "\t\t" << arregloResultado[i] << endl;
    }

    // Verificación de correctitud
    cout << endl << "=== VERIFICACION DE CORRECTITUD ===" << endl;
    bool correcto = true;
    for (int i = 0; i < N; i++) {
        if (arregloResultado[i] != arreglo1[i] + arreglo2[i]) {
            correcto = false;
            cout << "Error en el indice " << i << endl;
            break;
        }
    }

    if (correcto) {
        cout << "✓ Todos los elementos fueron sumados correctamente!" << endl;
    }
    else {
        cout << "✗ Se encontraron errores en la suma" << endl;
    }
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
