#ifndef VERBETE_H
#define VERBETE_H
#include <iostream>
#include <fstream>
#include "Fila_Significado.hpp"
using namespace std;

class Verbete{
    private:
        char tipo;
        string verbete;
        string significado;
        Fila_Significado fila_significado;

    public:
        Verbete();
        Verbete(string verbete);
        Verbete(char tipo, string verbete, string significado);
        void inserir_significado(string significado);
        void imprimir_significados();
        string get_Verbete();
        void set_Verbete(string verbete);
        string get_Significado();
};

#endif