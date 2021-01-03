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

/*
Falta:
    Entregar por pantalla:
        Solución (Avión y su instante de tiempo)
        Costo total
        Tiempo de cómputo
    Para hacer lo anterior, debo implementar la función objetivo y los prints
    necesarios

    Implementar mostrar por pantalla y registrar en un archivo de texto:
        Cantidad de instanciaciones
        Cantidad de chequeos
        Cantidad de retornos
        Subconjunto de aviones que alcanzó a asignarse un tiempo de aterrizaje
        Tiempo de ejecución
*/

// #include "includes.h"
// #include "globales.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <map>
using namespace std;

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
        vector<int> conjuntoconflicto;
        int nro_avion;
};

class Solucion {
    public:
        map<int, int> AvioneseInstante;
        int Costo;
        int Tiempo;
        int Cant_Instanciaciones;
        int Cant_Chequeos;
        int Cant_Retornos;
};

Solucion Solucion_current;
Solucion Solucion_best;

std::vector<Avion> deepCopydeAviones(vector<Avion> Aviones, int P) {
    vector<Avion> Aviones_copia(P, Avion());
    vector<Avion>::iterator it;
    int contador_aviones = 0;
    for(it = Aviones.begin(); it != Aviones.end(); ++it) {
        Aviones_copia[contador_aviones].E = Aviones[contador_aviones].E;
        Aviones_copia[contador_aviones].T = Aviones[contador_aviones].T;
        Aviones_copia[contador_aviones].L = Aviones[contador_aviones].L;
        Aviones_copia[contador_aviones].g = Aviones[contador_aviones].g;
        Aviones_copia[contador_aviones].h = Aviones[contador_aviones].h;
        Aviones_copia[contador_aviones].indice = Aviones[contador_aviones].indice;
        Aviones_copia[contador_aviones].nro_avion = Aviones[contador_aviones].nro_avion;
        for(int k = Aviones_copia[contador_aviones].E; k <= Aviones[contador_aviones].L; k++) {
            Aviones_copia[contador_aviones].dominio.push_back(k);
        }
        for(int l = 0; l < P; l++) {
            Aviones_copia[contador_aviones].conjuntoconflicto.push_back(-1);
        }
        contador_aviones += 1;
    }
    return Aviones_copia;
}



vector<int> agregarindiceaconflictos(vector<int> conjuntoconflicto, int Indice, int P) {
    for(int i = 0; i < P; i++) {
        if(conjuntoconflicto[i] == -1) { // Si ya llego al final
            conjuntoconflicto[i] = Indice;
            return conjuntoconflicto;
        }
        if(conjuntoconflicto[i] == Indice) { // Quiere decir que ya esta
            return conjuntoconflicto;
        }
    }
    return conjuntoconflicto;
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
                // ACA SE CUENTAN LOS CHEQUEOS
                if(*x_j < x_i + MATRIZ_DISTANCIAS[avion_no_instanciado->indice][Indice] && *x_j > x_i - MATRIZ_DISTANCIAS[avion_no_instanciado->indice][Indice]) {
                    // Significa que debo borrar x_j de avion_no_instanciado->dominio
                    copia_dominio.remove(*x_j);
                    // Agregar Indice a avion_no_instanciado->conjuntoconflictos
                    avion_no_instanciado->conjuntoconflicto = agregarindiceaconflictos(avion_no_instanciado->conjuntoconflicto, Indice, P);
                }
            }
            avion_no_instanciado->dominio = copia_dominio;
        }
    }
    // Para printear en caso de debugear
    // for(avion_no_instanciado = Aviones_copia.begin(); avion_no_instanciado != Aviones_copia.end(); ++avion_no_instanciado) {
    //     // list<int>::iterator x_j;
    //     vector<int>::iterator x_j;
    //     cout << "indice: " << avion_no_instanciado->indice << endl;
    //     cout << "conjunto conflicto: " << endl;
    //     for(x_j = avion_no_instanciado->conjuntoconflicto.begin(); x_j != avion_no_instanciado->conjuntoconflicto.end(); ++x_j) {
    //         cout << *x_j;
    //     }
    //     cout << endl;

    // }
    return Aviones_copia;
}



int escogerIndiceSaltoInteligente(vector<int> conjuntoconflicto) {
    int mayor = -9999;
    vector<int>::iterator iterador;
    for(iterador = conjuntoconflicto.begin(); iterador != conjuntoconflicto.end(); ++iterador) {
        if(*iterador > mayor) {
            mayor = *iterador;
        }
    }
    return mayor;
}

vector<int> HayAlgunDominioVacio(vector<Avion> Aviones_nueva_copia) {
    vector<Avion>::iterator avion;
    vector<int> Respuesta;
    for(avion = Aviones_nueva_copia.begin(); avion != Aviones_nueva_copia.end(); ++avion) {
        if(avion->dominio.empty()) { // Si esta vacio, retornar [1, escogerIndiceSaltoInteligente]
            Respuesta.push_back(1);
            Respuesta.push_back(escogerIndiceSaltoInteligente(avion->conjuntoconflicto));
            return Respuesta;
        }
    }
    Respuesta.push_back(0);
    return Respuesta;
}

int ALSP_v2(int** MATRIZ_DISTANCIAS, vector<Avion> Aviones_copia, int Indice, int Valor, int* Solucion, int P) {
    // Retorna: estado
    // Si estado == -2, significa que se encontró una solución y la rama está libre de saltos inteligentes (CBJ)
    // En caso que no esté libre de saltos inteligentes, estado tomará el valor del índice del avión
    // al cual se debe saltar, basándose en el conjunto de conflicto de la variable con dominio vacío
    Solucion[Indice] = Valor;
    // ACA SE CUENTAN LAS INSTANCIACIONES
    if(Indice >= P -1) {
        // Print solucion
        for(int i = 0; i < P; i++) {
            cout << Solucion[i] << ",";
        }
        cout << endl;
        // ACA SE PUEDEN CONTAR RETORNOS
        return -2;
    }

    vector<Avion> Aviones_nueva_copia;
    Aviones_nueva_copia = Filtrar_espacio_busqueda(MATRIZ_DISTANCIAS, Aviones_copia, Indice, Valor, P);
    vector<int> Respuesta = HayAlgunDominioVacio(Aviones_nueva_copia);
    if(Respuesta[0] == 1) {
        // ACA SE PUEDEN CONTAR RETORNOS
        return Respuesta[1];
    }
    int Solucion_nueva_copia[P];
    for(int i = 0; i < P; i++) {
        Solucion_nueva_copia[i] = Solucion[i];
    }

    list<int>::iterator valor_siguiente_dominio;
    for(valor_siguiente_dominio = Aviones_nueva_copia[Indice + 1].dominio.begin(); valor_siguiente_dominio != Aviones_nueva_copia[Indice + 1].dominio.end(); ++valor_siguiente_dominio) {
        int estado = ALSP_v2(MATRIZ_DISTANCIAS, Aviones_nueva_copia, Indice + 1, *valor_siguiente_dominio, Solucion_nueva_copia, P);
        if(estado != -2 && estado != Indice + 1) {
            // Si estado es diferente de -2 (no + CBJ) y no es Indice + 1, return estado
            // ACA SE PUEDEN CONTAR RETORNOS
            return estado;
        }
    }
    // ACA SE PUEDEN CONTAR RETORNOS
    return -2;
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
        Aviones[contador_aviones].nro_avion = contador_aviones;
        for(int k = Aviones[contador_aviones].E; k <= Aviones[contador_aviones].L; k++) {
            Aviones[contador_aviones].dominio.push_back(k);
        }
        for(int l = 0; l < P; l++) {
            Aviones[contador_aviones].conjuntoconflicto.push_back(-1); // -1 significa no conflictos (por ahora)
        }
        
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
        ALSP_v2(MATRIZ_DISTANCIAS, Aviones_copia, 0, *valor, Solucion, P);
    }
    return 0;
}