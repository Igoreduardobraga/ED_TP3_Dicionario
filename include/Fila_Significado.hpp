#ifndef FILA_SIGNIFICADO_H
#define FILA_SIGNIFICADO_H
#include <iostream>
#include <fstream>
#include <cstddef>
#include <new>
using namespace std;

typedef string TipoItem;

class No_Fila{
  public:
    TipoItem significado;
    No_Fila* proximo;
};

class Fila_Significado{
    private:
        No_Fila* primeiro;
        No_Fila* ultimo;
        unsigned short int tamanho;

    public:
        Fila_Significado();
        ~Fila_Significado();
        bool estavazio();
        bool estacheio(); 
        void inserir(TipoItem significado); 
        void remover();
        void imprimir();
        int get_tamanho();
};

#endif