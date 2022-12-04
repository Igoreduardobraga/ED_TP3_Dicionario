#ifndef FILA_SIGNIFICADO
#define FILA_SIGNIFICADO
using namespace std;
#include <iostream>

typedef string TipoItem;

class No
{
  public:
    TipoItem significado;
    No* proximo;
};

class Fila_Significado{
    private:
        No* primeiro;
        No* ultimo;

    public:
        Fila_Significado();
        ~Fila_Significado();
        bool estavazio();
        bool estacheio();
        void inserir(TipoItem item);
        void remover();
        void imprimir();
};

#endif