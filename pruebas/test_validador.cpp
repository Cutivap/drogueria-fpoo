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
        stringstream in("\n   \nIbuprofeno 400 mg\n");
        stringstream out;
        CValidador v(in, out);
        CHECK_EQ(v.leerTextoNoVacio("nombre: "), "Ibuprofeno 400 mg");
    }

    SECCION("CValidador: esFechaValida");
    CHECK(CValidador::esFechaValida("07-10-2026"));
    CHECK(CValidador::esFechaValida("29-02-2024"));
    CHECK(!CValidador::esFechaValida("29-02-2023"));
    CHECK(!CValidador::esFechaValida("31-04-2026"));
    CHECK(!CValidador::esFechaValida("7-10-2026"));
    CHECK(!CValidador::esFechaValida("hola"));

    // TODO (Grupo 3): float positivo, fecha con letras, entrada que se termina (EOF),
    // límites del rango (minimo y maximo incluidos), años bisiestos (1900, 2000), etc.

    return RESUMEN();
}
