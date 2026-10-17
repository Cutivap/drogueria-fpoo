/*
    Proyecto: Drogueria - FPOO - Universidad del Valle
    Módulo: Validación de entradas (GRUPO 3)

    ESTE ARCHIVO ES TUYO: reemplaza los STUB por la implementación real.
    (El STUB actual NO valida nada: solo lee la siguiente palabra.)
*/
#include "CValidador.h"
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

CValidador::CValidador(istream& entrada_, ostream& salida_) : entrada(entrada_), salida(salida_) {
}

int CValidador::leerEntero(string mensaje, int minimo, int maximo){
    string auxLinea; // linea auxiliar
    while (true){
        salida << mensaje;

        if (!getline(entrada, auxLinea)){
            return minimo;
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
    string auxLinea; // linea auxiliar
    while (true){
        salida << mensaje;

        if (!getline(entrada, auxLinea)){// si logra leer la linea el metodo sigue, sino se retorna 0. Si no logra leer la linea es muy problable que sea porque se llega a eof
            return 0; // al retornar 0 se sale del metodo
        }

        stringstream ss(auxLinea);
        float valor;
        char extra;

        if (ss >> valor && !(ss >> extra) && valor > 0){
            return valor; // al retornar el valor valido se sale del metodo
        }
        /* En este if se evaluan 3 condiciones con el operador &&, la unica manera que el if se ejecute es que todas sean true
        *la primera (ss >> valor) devuelve true cuando ss lee un numero real, o sea que si lee cualquier otra cosa decuelve false, el if no entra *y se repite el ciclo
        * La segunda (!(ss >> extra)) devuelve true cuando ss falla en leer el siguiente caracter despues de la primera condicion, o sea que si *hay cualquier cosa despues del real que se leyo la condicion devuelve false y el if no entra
        * La tercera (valor > 0) revisa si el valor es positivo, si no devuelve false y el if no entra */
    }

}

string CValidador::leerTextoNoVacio(string mensaje){
string texto;

    while (true) {
        salida << mensaje;

        // Si hay un error al leer la entrada, salimos devolviendo vacío
        if (!getline(entrada, texto)) {
            return "";
        }

        // Verificamos si el texto tiene al menos un caracter real (que no sea espacio)
        bool tieneContenido = false;
        for (char c : texto) {
            // Usamos unsigned char por seguridad interna de C++ con caracteres especiales
            if (!isspace(static_cast<unsigned char>(c))) {
                tieneContenido = true;
                break; // Encontramos algo válido, no necesitamos seguir buscando
            }
        }

        // Si encontramos contenido real, lo devolvemos
        if (tieneContenido) {
            return texto;
        }

        // Si eran puros espacios, el ciclo 'while' vuelve a pedir el texto amablemente.
    }
}

string CValidador::leerFecha(string mensaje){
while (true) {
        // Primero nos aseguramos de que escriba algo que no esté vacío
        string fecha = leerTextoNoVacio(mensaje);

        // Si la entrada se canceló, devolvemos vacío
        if (fecha.empty()) {
            return "";
        }

        // Si la fecha pasa la prueba de calendario, la aceptamos
        if (esFechaValida(fecha)) {
            return fecha;
        }

        salida << "Fecha inválida o inexistente en el calendario. Inténtalo de nuevo.\n";
    }
}

bool CValidador::esFechaValida(string fecha){
    // Paso A: Validar la estructura visual básica (debe medir exactamente 10 caracteres y tener guiones en su lugar)
    if (fecha.length() != 10 || fecha[2] != '-' || fecha[5] != '-') {
        return false;
    }

    // Paso B: Verificar que el resto de posiciones sean números (del 0 al 9)
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; // Saltamos los guiones porque ya sabemos que están ahí

        if (!isdigit(static_cast<unsigned char>(fecha[i]))) {
            return false; // Si hay una letra o símbolo extraño, la fecha no sirve
        }
    }

    // Paso C: Separar la fecha en día, mes y año convirtiéndolos a números enteros
    int dia = stoi(fecha.substr(0, 2));
    int mes = stoi(fecha.substr(3, 2));
    int anio = stoi(fecha.substr(6, 4));

    // Paso D: Validar rangos lógicos básicos del calendario
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1) {
        return false;
    }

    // Paso E: Definir cuántos días tiene cada mes por defecto (de enero a diciembre)
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Paso F: Ajustar febrero si el año es bisiesto (29 días en vez de 28)
    bool esBisiesto = (anio % 400 == 0) || (anio % 4 == 0 && anio % 100 != 0);
    if (esBisiesto) {
        diasPorMes[1] = 29;
    }

    // Paso G: Verificar que el día no rebase el límite máximo del mes correspondiente
    return dia <= diasPorMes[mes - 1];
}
