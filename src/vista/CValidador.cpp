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

      // Si hay un error al leer la entrada, salimos devolviendo vacío, por tal razón ponemos la negación cuando obtenemos la entrada
      if (!getline(entrada, texto)) {
          return "";
      }
      // Verificamos si el texto tiene al menos un caracter real (que no sea espacio)
      bool tieneContenido = false;
        for (char c : texto) {
            // Usamos unsigned char por seguridad interna de C++ con caracteres especiales por medio del operador de conversión static_cast,
            // aplicando el operador isspace para verificar si es un espacio y la negación para determinar si es un caracter válido
            if (!isspace(static_cast<unsigned char>(c))) {
              tieneContenido = true;
                break; // Encontramos algo válido, no necesitamos seguir buscando
            }
        }
      // Si encontramos contenido real, lo devolvemos
      if (tieneContenido) {
          return texto;
      }
        // Si eran puros espacios, el ciclo 'while' vuelve a pedir el texto amablemente :)
    }
}


string CValidador::leerFecha(string mensaje) {
  while (true) {
      // Leer el texto ingresado por el usuario con ayuda del método leerTextoNoVacio, que asegura que no sea una cadena vacía o solo espacios.
      string fecha = leerTextoNoVacio(mensaje);

      // Si la entrada se terminó se devuelve una cadena vacía.
      if (fecha.empty()) {
          return "";
      }

      // Eliminar espacios al inicio y al final con el tipo de dato size_t que es un dato entero sin signo,
      // se usa para representar tamaños y posiciones en contenedores, como strings o vectores.
      // Se usa size_t porque es el tipo de dato que devuelve find_first_not_of y find_last_not_of.
      // el fin_first_not_of devuelve la posición del primer caracter que no es un espacio, dado que le pasamos " \t\r\n" como argumento, que representa espacios, tabulaciones y saltos de línea.
      // Por tanto, ignorará aquellos caracteres al inicio de la cadena que sean espacios, tabulaciones o saltos de línea.
      // Se enfocará en encontrar uno que no coincida y se detendrá ahí, devolviendo su posición. Si no encuentra ninguno,
      // devuelve string::npos, que es una constante especial que indica que no se encontró ningún caracter válido.
      size_t inicio = fecha.find_first_not_of(" \t\r\n");

      // Aquí verificamos si inicio es igual a string::npos, lo que significa que no se encontró ningún caracter válido en la cadena.
      if (inicio == string::npos) {
          continue;
      }

      // De manera similar, find_last_not_of busca el último caracter que no sea un espacio, tabulación o salto de línea.
      // Es el mismo proceso, solo que recorre la cadena desde el final hacia el inicio. Devuelve la posición del último caracter válido.
      // Ignorando de la misma forma los espacios, tabulaciones y saltos de línea al final de la cadena.
      size_t fin = fecha.find_last_not_of(" \t\r\n");

      // Ahora, con las posiciones de inicio y fin, podemos extraer la subcadena que contiene la fecha sin espacios al inicio ni al final.
      // substr toma la posición de inicio y la longitud de la subcadena que queremos extraer, que es fin - inicio + 1 en este caso,
      // para incluir el caracter en la posición fin. Es decir se extrae la parte de la cadena que está entre inicio y fin, eliminando los espacios al inicio y al final.
      fecha = fecha.substr(inicio, fin - inicio + 1);

      // Validamos la fecha después de eliminar los espacios.
      if (esFechaValida(fecha)) {
          return fecha;
      }

      // Si la fecha no es válida, se informa al usuario.
      salida << "Fecha inválida o inexistente en el calendario.\nInténtalo de nuevo.\n";
    }
}


bool CValidador::esFechaValida(string fecha){
    // Paso A: Validar la estructura visual básica (debe medir exactamente 10 caracteres y tener guiones en su lugar,
    // exactamente en la posición número 2 y en la 5)
    if (fecha.length() != 10 || fecha[2] != '-' || fecha[5] != '-') {
        return false;
    }

    // Paso B: Verificar que el resto de posiciones sean números (del 0 al 9)
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; // Saltamos los guiones porque ya sabemos que están ahí, así que solo le damos continue para verificar lo demás

        if (!isdigit(static_cast<unsigned char>(fecha[i]))) {
            return false; // Si hay una letra o símbolo extraño, la fecha no sirve y devolverá false si es que se cumple la condición de arriba
        }
    }

    // Paso C: Separar la fecha en día, mes y año convirtiéndolos a números enteros. Recordemos que es un string,
    //así que usamos substr para obtener las partes y luego stoi para convertirlas a enteros.
    int dia = stoi(fecha.substr(0, 2));
    int mes = stoi(fecha.substr(3, 2));
    int anio = stoi(fecha.substr(6, 4));

    // Paso D: Validar rangos lógicos básicos del calendario y rechazará todo ello si no cumple con las condiciones de arriba.
    // Por ejemplo, no puede haber un mes 13 ni un día 0.
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1) {
        return false;
    }

    // Paso E: Definir cuántos días tiene cada mes por defecto (de enero a diciembre) este vector tendrá 12 posiciones,
    // cada una representando un mes del año, y el valor en cada posición será la cantidad de días que tiene ese mes. Por ejemplo, enero tiene 31 días, febrero tiene 28 días (o 29 si es bisiesto), marzo tiene 31 días, y así sucesivamente.
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Paso F: Definición lógica de año Bisiesto y en el que se busca ajustar febrero si el año es bisiesto (29 días en vez de 28)
    bool esBisiesto = (anio % 400 == 0) || (anio % 4 == 0 && anio % 100 != 0);
    if (esBisiesto) {
        diasPorMes[1] = 29;
    }

    // Paso G: Verificar que el día no rebase el límite máximo del mes correspondiente. Recordemos que se resta 1,
    // dado que se cuenta desde el indice 0, por lo que enero es 0, febrero es 1, marzo es 2, y así sucesivamente. Por eso se hace mes - 1 para obtener el índice correcto en el vector diasPorMes.Al final, solo se verifica si es mayor o igual al día máximo permitido para ese mes. Si es mayor, la fecha no es válida y se devuelve false.
    return dia <= diasPorMes[mes - 1];
}
