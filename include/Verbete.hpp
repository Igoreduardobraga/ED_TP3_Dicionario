#ifndef VERBETE_H
#define VERBETE_H
#include <iostream>
#include "Fila_Significado.hpp"
using namespace std;

class Verbete{
    private:
        char tipo;
        string verbete;
        string significado;
        Fila_Significado fila_significado;

    public:
        Verbete(){}
        Verbete(string verbete);
        Verbete(char tipo, string verbete, string significado);
        void inserir_significado(string significado);
        void imprimir_significado(ofstream *saida);
        string get_Verbete();
        string get_Significado();
};

#endif