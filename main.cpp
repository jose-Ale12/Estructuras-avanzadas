#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

// Trees
#include "BinarySearchTree.h"
#include "AVLTree.h"

using namespace std;
using namespace std::chrono;

// Funcion para medir el tiempo de insercion y busqueda en un BST
void benchmarkBST(int n) {
    cout << "===========================================================" << endl;
    cout << "  Benchmark con N = " << n << " datos" << endl;
    cout << "===========================================================" << endl;

    // Generar datos aleatorios sin repetidos
    // Usamos un vector con valores 1..n y lo mezclamos
    vector<int> datos(n);
    for (int i = 0; i < n; i++) {
        datos[i] = i + 1;
    }

    // Mezclar para insertar en orden aleatorio (evitar arbol degenerado)
    mt19937 rng(42); // semilla fija para reproducibilidad
    shuffle(datos.begin(), datos.end(), rng);

    // ------ INSERCION ------
    BinarySearchTree<int> tree;

    auto startInsert = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        tree.insert(datos[i]);
    }
    auto endInsert = high_resolution_clock::now();

    auto durationInsert = duration_cast<milliseconds>(endInsert - startInsert);
    cout << "  Tiempo de insercion de " << n << " elementos: "
         << durationInsert.count() << " ms" << endl;

    // ------ BUSQUEDA: Mejor caso (raiz) ------
    // Buscar el primer elemento insertado (probablemente cerca de la raiz)
    int buscarMejor = datos[0];
    auto startBest = high_resolution_clock::now();
    auto resultado = tree.find(buscarMejor);
    auto endBest = high_resolution_clock::now();

    auto durationBest = duration_cast<nanoseconds>(endBest - startBest);
    cout << "  Busqueda mejor caso (elemento " << buscarMejor << "): "
         << durationBest.count() << " ns";
    if (resultado != nullptr)
        cout << " -> Encontrado" << endl;
    else
        cout << " -> No encontrado" << endl;

    // ------ BUSQUEDA: Caso promedio (buscar varios elementos aleatorios) ------
    int numBusquedas = min(n, 1000); // buscar hasta 1000 elementos
    shuffle(datos.begin(), datos.end(), rng);

    auto startAvg = high_resolution_clock::now();
    for (int i = 0; i < numBusquedas; i++) {
        tree.find(datos[i]);
    }
    auto endAvg = high_resolution_clock::now();

    auto durationAvg = duration_cast<nanoseconds>(endAvg - startAvg);
    double promedioNs = (double)durationAvg.count() / numBusquedas;
    cout << "  Busqueda caso promedio (" << numBusquedas << " busquedas): "
         << fixed << setprecision(2) << promedioNs << " ns por busqueda" << endl;

    // ------ BUSQUEDA: Peor caso (elemento que NO existe) ------
    int buscarPeor = n + 999; // no existe en el arbol
    auto startWorst = high_resolution_clock::now();
    auto resultadoPeor = tree.find(buscarPeor);
    auto endWorst = high_resolution_clock::now();

    auto durationWorst = duration_cast<nanoseconds>(endWorst - startWorst);
    cout << "  Busqueda peor caso (elemento " << buscarPeor << " inexistente): "
         << durationWorst.count() << " ns";
    if (resultadoPeor != nullptr)
        cout << " -> Encontrado" << endl;
    else
        cout << " -> No encontrado" << endl;

    cout << "-----------------------------------------------------------" << endl;
    cout << endl;
}

// Funcion para medir el tiempo de insercion y busqueda en un AVL
void benchmarkAVL(int n) {
    cout << "===========================================================" << endl;
    cout << "  Benchmark AVL con N = " << n << " datos" << endl;
    cout << "===========================================================" << endl;

    // Generar datos aleatorios sin repetidos
    vector<int> datos(n);
    for (int i = 0; i < n; i++) {
        datos[i] = i + 1;
    }

    // Mezclar para insertar en orden aleatorio
    mt19937 rng(42); // semilla fija para reproducibilidad
    shuffle(datos.begin(), datos.end(), rng);

    // ------ INSERCION ------
    AVLTree<int> tree;

    auto startInsert = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        tree.insert(datos[i]);
    }
    auto endInsert = high_resolution_clock::now();

    auto durationInsert = duration_cast<milliseconds>(endInsert - startInsert);
    cout << "  Tiempo de insercion de " << n << " elementos: "
         << durationInsert.count() << " ms" << endl;

    // ------ BUSQUEDA: Mejor caso (raiz) ------
    int buscarMejor = datos[0];
    auto startBest = high_resolution_clock::now();
    auto resultado = tree.find(buscarMejor);
    auto endBest = high_resolution_clock::now();

    auto durationBest = duration_cast<nanoseconds>(endBest - startBest);
    cout << "  Busqueda mejor caso (elemento " << buscarMejor << "): "
         << durationBest.count() << " ns";
    if (resultado != nullptr)
        cout << " -> Encontrado" << endl;
    else
        cout << " -> No encontrado" << endl;

    // ------ BUSQUEDA: Caso promedio ------
    int numBusquedas = min(n, 1000);
    shuffle(datos.begin(), datos.end(), rng);

    auto startAvg = high_resolution_clock::now();
    for (int i = 0; i < numBusquedas; i++) {
        tree.find(datos[i]);
    }
    auto endAvg = high_resolution_clock::now();

    auto durationAvg = duration_cast<nanoseconds>(endAvg - startAvg);
    double promedioNs = (double)durationAvg.count() / numBusquedas;
    cout << "  Busqueda caso promedio (" << numBusquedas << " busquedas): "
         << fixed << setprecision(2) << promedioNs << " ns por busqueda" << endl;

    // ------ BUSQUEDA: Peor caso (elemento inexistente) ------
    int buscarPeor = n + 999;
    auto startWorst = high_resolution_clock::now();
    auto resultadoPeor = tree.find(buscarPeor);
    auto endWorst = high_resolution_clock::now();

    auto durationWorst = duration_cast<nanoseconds>(endWorst - startWorst);
    cout << "  Busqueda peor caso (elemento " << buscarPeor << " inexistente): "
         << durationWorst.count() << " ns";
    if (resultadoPeor != nullptr)
        cout << " -> Encontrado" << endl;
    else
        cout << " -> No encontrado" << endl;

    cout << "-----------------------------------------------------------" << endl;
    cout << endl;
}

int main() {
    cout << endl;
    cout << "###########################################################" << endl;
    cout << "#   BENCHMARK: Busqueda en Arbol BST y AVL                #" << endl;
    cout << "#   Midiendo tiempos de ejecucion con diferentes N        #" << endl;
    cout << "###########################################################" << endl;
    cout << endl;

    // tamanios solicitados 
    int tamanos[] = {100, 10000, 1000000};

    // ===== BENCHMARK BST =====
    cout << "***********************************************************" << endl;
    cout << "*                    ARBOL BST                            *" << endl;
    cout << "***********************************************************" << endl;
    cout << endl;
    for (int n : tamanos) {
        benchmarkBST(n);
    }

    // ===== BENCHMARK AVL =====
    cout << "***********************************************************" << endl;
    cout << "*                    ARBOL AVL                            *" << endl;
    cout << "***********************************************************" << endl;
    cout << endl;
    for (int n : tamanos) {
        benchmarkAVL(n);
    }

    // Resumen final
    cout << "###########################################################" << endl;
    cout << "#   Benchmark BST y AVL completado exitosamente!          #" << endl;
    cout << "###########################################################" << endl;

    return 0;
}