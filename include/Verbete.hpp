#ifndef VERBETE_H
#define VERBETE_H
#include <iostream>
#include "Fila_Significado.hpp"
using namespace std;

class Verbete{
    private:
        char tipo;
        string verbete;
        Fila_Significado significado;

    public:
        Verbete(){}
        Verbete(string verbete);
        Verbete(char tipo, string verbete, string significado);
        void imprimir_significado();
        string get_Verbete();
};

#endif