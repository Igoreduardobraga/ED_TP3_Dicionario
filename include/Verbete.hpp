#ifndef VERBETE_H
#define VERBETE_H
#include <iostream>
#include <fstream>
#include "Verbete.hpp"
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
        Verbete(char tipo, string verbete, string significado);
        Verbete(string verbete);
        void inserir_significado(string significado);
        void imprimir_significados();
        char get_Tipo();
        string get_Verbete();
        string get_Significado();
        int get_TamanhoFilaSignificados();
};

#endif