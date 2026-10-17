/*
    Proyecto: Drogueria - FPOO - Universidad del Valle
    Módulo: Validación de entradas (GRUPO 3)

    ESTE ARCHIVO ES TUYO: reemplaza los STUB por la implementación real.
    (El STUB actual NO valida nada: solo lee la siguiente palabra.)
*/
#include "CValidador.h"
#include <sstream>
using namespace std;

CValidador::CValidador(istream& entrada_, ostream& salida_) : entrada(entrada_), salida(salida_) {
}

int CValidador::leerEntero(string mensaje, int minimo, int maximo){
    // STUB (Grupo 3): implementar
    string auxLinea; // linea auxiliar 
    while (true){
        salida << mensaje;

        if (!getline(entrada, auxLinea)){ // si logra leer la linea el metodo sigue, sino se retorna minimo. Si no logra leer la linea es muy problable que sea porque se llega a eof
            return minimo; // al retornar minimo se sale del metodo
        }

        stringstream ss(auxLinea); //stringstream con la linea auxiliar para validar que la linea que lee getline() solo sea un entero
        int valor;
        char extra;

        if (ss >> valor && !(ss >> extra) && valor >= minimo && valor <= maximo){
            return valor;// al retornar al valor valido se sale del metodo
        }
        /* En este if se evaluan 4 condiciones con el operador &&, la unica manera que el if se ejecute es que todas sean true 
        *la primera (ss >> valor) es true cuando ss lee un numero entero, o sea que si lee cualquier otra cosa es false, el if no entra y se *repite el ciclo
        * La segunda (!(ss >> extra)) es true cuando ss falla en leer el siguiente caracter despues de la primera condicion, o sea que si hay *cualquier cosa despues del entero que se leyo la condicion es false y el if no entra
        * La tercera y cuarta (valor >= minimo && valor <=maximo) revisan si el valor esta en el rango [minimo, maximo] si valor es mayor a *maximo o menor a minimo, sus condiciones fallan y el if no entra */     
    }
}

float CValidador::leerFloatPositivo(string mensaje){
    // STUB (Grupo 3): implementar
    float valor = 0;
    salida << mensaje;
    entrada >> valor;
    return valor;
}

string CValidador::leerTextoNoVacio(string mensaje){
    // STUB (Grupo 3): implementar
    string texto;
    salida << mensaje;
    entrada >> texto;
    return texto;
}

string CValidador::leerFecha(string mensaje){
    // STUB (Grupo 3): implementar
    string texto;
    salida << mensaje;
    entrada >> texto;
    return texto;
}

bool CValidador::esFechaValida(string fecha){
    // STUB (Grupo 3): implementar
    return true;
}
