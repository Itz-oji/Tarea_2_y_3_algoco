#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

string generarPalabra(int longitud) {
    string palabra;
    for (int i = 0; i < longitud; ++i) {
        palabra += 'a' + rand() % 26;
    }
    return palabra;
}

string generarPalabraTranspuesta(string palabra) {
    if (palabra.size() < 2) return palabra;
    int numTransposiciones = rand() % min(4, static_cast<int>(palabra.size() - 1)) + 1;

    for (int i = 0; i < numTransposiciones; ++i) {
        int pos = rand() % (palabra.size() - 1); 
        swap(palabra[pos], palabra[pos + 1]);
    }
    return palabra;
}


void crearDatasets() {
    srand(time(0));

    for (int i = 1; i <= 5; ++i) { 
        string nombreArchivo = "dataset" + to_string(i) + ".txt";
        ofstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            cerr << "Error al crear el archivo: " << nombreArchivo << endl;
            continue;
        }

        for (int longitud = 1; longitud <= 16; ++longitud) {
            string palabra1, palabra2;

            
            if (rand() % 5 == 0) {
                palabra1 = "";
            } else {
                palabra1 = generarPalabra(longitud);
            }

            int opcion = rand() % 4;

            if (opcion == 0) {
                palabra2 = "";
            } else if (opcion == 1) { 
                palabra2 = generarPalabraTranspuesta(palabra1);
            } else if (opcion == 2) { 
                palabra2 = generarPalabra(rand() % longitud);
            } else { 
                palabra2 = generarPalabra(longitud);
            }

            archivo << palabra1 << endl; 
            archivo << palabra2 << endl; 
        }

        archivo.close();
        cout << "Archivo " << nombreArchivo << " creado con éxito." << endl;
    }
}

int main() {
    crearDatasets();
    return 0;
}


//c++ dataset.cpp -o dataset
//dataset