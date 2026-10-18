// Pruebas de CValidador. Responsable: GRUPO 3
#include <sstream>
#include "minitest.h"
#include "CValidador.h"
using namespace std;

int main(){
    SECCION("CValidador: leerEntero insiste hasta recibir un valor valido");
    {
        stringstream in("abc\n7\n");
        stringstream out;
        CValidador v(in, out);
        CHECK_EQ(v.leerEntero("n: ", 1, 10), 7);
    }
    {
        stringstream in("50\n-3\n5\n");
        stringstream out;
        CValidador v(in, out);
        CHECK_EQ(v.leerEntero("n: ", 1, 10), 5);
    }
    {
        // probar los limites minimo y maximo permitidos dentro del rango
        stringstream in("1\n10\n"); 
        stringstream out;
        CValidador v(in, out);
        CHECK_EQ(v.leerEntero("n: ", 1, 10), 1);
        CHECK_EQ(v.leerEntero("n: ", 1, 10), 10);
    }
    {
        // introducir letras, lineas vacias y entradas mal formadas antes de un acierto
        stringstream in("\n \n8\n");
        stringstream out;
        CValidador v(in, out);
        CHECK_EQ(v.leerEntero("n: ", 1, 10), 8);
    }
    SECCION("CValidador: leerFloatPositivo");
    {
        // verificar numeros positivos, cero, negativos y entradas no numericas
        stringstream in("texto\n-5.5\n0\n4.2\n");
        stringstream out;
        CValidador v(in, out);
        CHECK_NEAR(v.leerFloatPositivo("precio: "), 4.2f, 0.001f); // check_near verifica numeros reales (float) con una tolerancia de error
    }
    {
        // comprobar el comportamiento cuando se termina la entrada (eof)
        stringstream in("texto_invalido\n");
        stringstream out;
        CValidador v(in, out); // si hay eof, debe salir del ciclo y devolver un valor de error
        CHECK_NEAR(v.leerFloatPositivo("precio: "), 0.0f, 0.001f);
    }
    SECCION("CValidador: leerTextoNoVacio");
    {
        stringstream in("\n   \nIbuprofeno 400 mg\n");//crea un flujo de entrada que simula datos que ingresaria un usuaria.
        //se prueba el hipotetico de que el usuario ingrese un salto de linea, una cadena vacia y una cadena de texto
        stringstream out;
        CValidador v(in, out);
        CHECK_EQ(v.leerTextoNoVacio("nombre: "), "Ibuprofeno 400 mg");//check equal, evalua que dos valores sean iguales
    }

    SECCION("CValidador: esFechaValida");
    {
        CHECK(CValidador::esFechaValida("07-10-2026"));//prueba una fecha con formato valido y rangos correctos de año un año no bisiesto
        CHECK(!CValidador::esFechaValida("31-04-2026"));//prueba una fecha con dias fuera de rango para un año no bisiesto
        CHECK(!CValidador::esFechaValida("7-13-2025"));//prueba una fecha con meses fuera de rango para un año no bisiesto
        CHECK(CValidador::esFechaValida("29-02-2024"));//prueba una fecha de un año bisiesto correcta
        CHECK(!CValidador::esFechaValida("29-02-2023"));//prueba una fecha fuera de rango para un año bisiesto 
        CHECK(CValidador::esFechaValida("29-02-2000"));//prueba una fecha en un año bisiesto centenario
        CHECK(!CValidador::esFechaValida("022-01-2018"));//prueba una fecha con un formato mas grande que 10 elementos de la cadena 
        CHECK(!CValidador::esFechaValida("-01-2018"));//prueba una fecha con un formato mas pequeño que 10 elementos
        CHECK(!CValidador::esFechaValida("11/09/2026"));// prueba una fecha con un separador de dias mes y año incorrecto
        CHECK(!CValidador::esFechaValida("hola"));//prueba el hipotetico de ingresar una cadena de letras
        CHECK(!CValidador::esFechaValida("   "));//prueba el hipotetico de ingresar una cadena vacia
        CHECK(!CValidador::esFechaValida("\n"));//prueba los saltos de linea
    }

    SECCION("CValidador: leerFecha");
    {
        {stringstream in("01-000-2023\n29-02-1900\naqui\n02-06-2006"); //probar consecutivas fechas incorrectas para asegurar que se vuelva a pedirla hasta conseguir uno valido
        stringstream out;
        CValidador v(in, out);
        CHECK_EQ(v.leerFecha("Ingrese la fecha: "), "02-06-2006");
        }
        {stringstream in("01-000-2023\n29-02-1900\naqui\n"); //probar si ninguno de los flujos arroja una fecha correcta se devuelva ""
        stringstream out;
        CValidador v(in, out);
        CHECK_EQ(v.leerFecha("Ingrese la fecha: "), "");
        }
    }
    // TODO (Grupo 3): float positivo, fecha con letras, entrada que se termina (EOF),
    // límites del rango (minimo y maximo incluidos), años bisiestos (1900, 2000), etc.
    
    return RESUMEN();
}
