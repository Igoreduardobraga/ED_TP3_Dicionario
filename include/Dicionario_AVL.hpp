#ifndef DICIONARIO_AVL
#define DICIONARIO_AVL
#include "Verbete.hpp"
#include <iostream>
using namespace std;
#include <fstream>

#define MAX_VERBETES 4997

struct No{
    Verbete verbete;
    No *esquerda;
    No *direita;
    int altura;
};

class Dicionario_AVL{
    private:

    public:
        void Destruir_Dicionario(No* Noatual);
        int altura(No *N);
        int max(int a, int b);
        No* NovoNo(Verbete verbete);
        No *Rotacao_Direita(No *y);
        No *Rotacao_Esquerda(No *x);
        int get_balanceamento(No *N);
        No* inserir(No* no, Verbete verbete);
        No * minValueNode(No* no);
        No* Remover_Verbetes(No* root);
        No* PesquisaRecursivo(No *no, string chave);
        void Imprimir_Dicionario(No *raiz, ofstream *saida);
};

#endif