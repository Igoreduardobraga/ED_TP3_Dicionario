#ifndef FILA_SIGNIFICADO_H
#define FILA_SIGNIFICADO_H
#include <iostream>
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

    public:
        Fila_Significado();
        ~Fila_Significado();
        bool estavazio();
        bool estacheio(); 
        void inserir(TipoItem significado); 
        void remover();
        void imprimir();
};

#endif