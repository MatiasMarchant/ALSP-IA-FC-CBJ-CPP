// Forward Checking + CBJ
// Matías Marchant 201673556-9

// PARA CRUZAR MATRIZ
// cout << endl;
// for(int i = 0; i < sizeof(MATRIZ_DISTANCIAS[0])/sizeof(*MATRIZ_DISTANCIAS[0]); i++) {
//     cout << "i: " << i << " " << MATRIZ_DISTANCIAS[1][i] << endl;
// }
// cout << endl;

// PARA ITERAR LISTA DE ENTEROS
// list<int>::iterator it;
// for(it = Aviones[0].dominio.begin(); it != Aviones[0].dominio.end(); ++it) {
//     cout << (*it) << endl;
// }

// #include "includes.h"
// #include "globales.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
using namespace std;

// GLOBAL VARIABLE
// vector<vector<int>> MATRIZ_DISTANCIAS;



// Clases
class Avion {
    public:
        int E;
        int T;
        int L;
        float g;
        float h;
        int indice;
        list<int> dominio;
        // Avion();
};

// Constructor de Avion
// Avion::Avion(int Ev, int Tv, int Lv, float gv, float hv, int indicev) {
//     E = Ev;
//     T = Tv;
//     L = Lv;
//     g = gv;
//     h = hv;
//     indice = indicev;
//     for(int i = Ev; i <= Lv; i++) {
//         dominio.push_back(i);
//     }
// }


std::vector<Avion> deepCopydeAviones(vector<Avion> Aviones, int P) {
    vector<Avion> Aviones_copia(P, Avion());
    vector<Avion>::iterator it;
    int contador_aviones = 0;
    for(it = Aviones.begin(); it != Aviones.end(); ++it) {
        // QUIZAS ACA TENIA QUE HACER it->E;
        Aviones_copia[contador_aviones].E = Aviones[contador_aviones].E;
        Aviones_copia[contador_aviones].T = Aviones[contador_aviones].T;
        Aviones_copia[contador_aviones].L = Aviones[contador_aviones].L;
        Aviones_copia[contador_aviones].g = Aviones[contador_aviones].g;
        Aviones_copia[contador_aviones].h = Aviones[contador_aviones].h;
        Aviones_copia[contador_aviones].indice = Aviones[contador_aviones].indice;
        for(int k = Aviones_copia[contador_aviones].E; k <= Aviones[contador_aviones].L; k++) {
            Aviones_copia[contador_aviones].dominio.push_back(k);
        }
        contador_aviones += 1;
    }
    return Aviones_copia;
}



vector<Avion> Filtrar_espacio_busqueda(int** MATRIZ_DISTANCIAS, vector<Avion> Aviones_copia, int Indice, int Valor, int P) {
    int x_i = Valor;
    vector<Avion> Aviones_nueva_copia = deepCopydeAviones(Aviones_copia, P);
    vector<Avion>::iterator avion_no_instanciado;
    for(avion_no_instanciado = Aviones_copia.begin(); avion_no_instanciado != Aviones_copia.end(); ++avion_no_instanciado) {
        if(avion_no_instanciado->indice >= Indice + 1) {
            list<int> copia_dominio(avion_no_instanciado->dominio);
            list<int>::iterator x_j;
            for(x_j = avion_no_instanciado->dominio.begin(); x_j != avion_no_instanciado->dominio.end(); ++x_j) {
                if(*x_j < x_i + MATRIZ_DISTANCIAS[avion_no_instanciado->indice][Indice] && *x_j > x_i - MATRIZ_DISTANCIAS[avion_no_instanciado->indice][Indice]) {
                    //cout << "entre aca" << endl;
                    // Significa que debo borrar x_j de avion_no_instanciado->dominio
                    copia_dominio.remove(*x_j);
                }
            }
            avion_no_instanciado->dominio = copia_dominio;
        }
    }
    // for(avion_no_instanciado = Aviones_copia.begin(); avion_no_instanciado != Aviones_copia.end(); ++avion_no_instanciado) {
    //     list<int>::iterator x_j;
    //     cout << "indice: " << avion_no_instanciado->indice << endl;
    //     for(x_j = avion_no_instanciado->dominio.begin(); x_j != avion_no_instanciado->dominio.end(); ++x_j) {
    //         cout << "x_j: " << *x_j << endl;
    //     }

    // }
    return Aviones_copia;
}


void ALSP(int** MATRIZ_DISTANCIAS, vector<Avion> Aviones_copia, int Indice, int Valor,  int* Solucion, int P) {
    Solucion[Indice] = Valor;
    
    // for(int i = 0; i < P; i++) {
    //     cout << Solucion[i] << endl;
    // }
    vector<Avion> Aviones_nueva_copia;
    if(Indice >= P - 1) {
        for(int i = 0; i < P; i++) {
            cout << Solucion[i] << ",";
        }
        cout << endl;
        return;
    }

    Aviones_nueva_copia = Filtrar_espacio_busqueda(MATRIZ_DISTANCIAS, Aviones_copia, Indice, Valor, P);
    int Solucion_nueva_copia[P];
    for(int i = 0; i < P; i++) {
        Solucion_nueva_copia[i] = Solucion[i];
    }

    list<int>::iterator valor_siguiente_dominio;
    for(valor_siguiente_dominio = Aviones_nueva_copia[Indice + 1].dominio.begin(); valor_siguiente_dominio != Aviones_nueva_copia[Indice + 1].dominio.end(); ++valor_siguiente_dominio) {
        ALSP(MATRIZ_DISTANCIAS, Aviones_nueva_copia, Indice + 1, *valor_siguiente_dominio, Solucion_nueva_copia, P);
    }
    return ;
}





int main(int argc, char *argv[]) {
    // Lectura de instancia
    string FileName(argv[1]);
    ifstream file_instancia(FileName);

    string line;
    string delimeter = " ";
    size_t pos = 0;
    string token;
    getline(file_instancia, line);
    pos = line.find(delimeter);
    token = line.substr(0, pos);
    line.erase(0, pos + delimeter.length());
    pos = line.find(delimeter);
    token = line.substr(0, pos);
    line.erase(0, pos + delimeter.length());
    int P = stoi(token);
    // int MATRIZ_DISTANCIAS[P][P];
    int **MATRIZ_DISTANCIAS = new int*[P];
    for(int i = 0; i < P; i++) {
        MATRIZ_DISTANCIAS[i] = new int[P];
    }
    

    // Vector de aviones
    vector <Avion> Aviones(P, Avion());

    
    
    
    int contador_aviones = 0;
    int contador_matrizfila = 0;
    for (int i = 0; i < P; i++) {
        getline(file_instancia, line);
        vector <float> arreglo_aux;
        int contador = 0;
        int contador_matrizcolumna = 0;

        pos = line.find(delimeter);
        token = line.substr(0, pos);
        line.erase(0, pos + delimeter.length());

        while((pos = line.find(delimeter)) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + delimeter.length());
            arreglo_aux.push_back(stof(token));
            
            contador += 1;
        }

        Aviones[contador_aviones].E = static_cast<int>(arreglo_aux[0]);
        Aviones[contador_aviones].T = static_cast<int>(arreglo_aux[1]);
        Aviones[contador_aviones].L = static_cast<int>(arreglo_aux[2]);
        Aviones[contador_aviones].g = arreglo_aux[3];
        Aviones[contador_aviones].h = arreglo_aux[4];
        Aviones[contador_aviones].indice = contador_aviones;
        for(int k = Aviones[contador_aviones].E; k <= Aviones[contador_aviones].L; k++) {
            Aviones[contador_aviones].dominio.push_back(k);
        }
        // Aviones[contador_aviones].dominio = 
        
        contador_aviones += 1;

        getline(file_instancia, line);
        pos = line.find(delimeter);
        token = line.substr(0, pos);
        line.erase(0, pos + delimeter.length());

        while((pos = line.find(delimeter)) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + delimeter.length());
            MATRIZ_DISTANCIAS[contador_matrizfila][contador_matrizcolumna] = stoi(token);
            contador_matrizcolumna += 1;
        }
        MATRIZ_DISTANCIAS[contador_matrizfila][contador_matrizcolumna] = stoi(line);
        contador_matrizfila += 1;
        contador_matrizcolumna = 0;
    }
    file_instancia.close();

    int Solucion[P];
    vector<Avion> Aviones_copia = deepCopydeAviones(Aviones, P);
    list<int>::iterator valor;
    for(valor = Aviones[0].dominio.begin(); valor != Aviones[0].dominio.end(); ++valor) {
        ALSP(MATRIZ_DISTANCIAS, Aviones_copia, 0, *valor, Solucion, P);
        // cout << "valor sin *: " << valor << endl;
        // cout << "valor con *: " << *valor << endl;
    }

    // for(int i = 0; i < P; i++) {
    //     for(int j = 0; j < P; j++) {
    //         cout << MATRIZ_DISTANCIAS[i][j];
    //     }
    //     cout << endl;
    // }
    // cout << MATRIZ_DISTANCIAS[0][0] << endl;
    return 0;
}