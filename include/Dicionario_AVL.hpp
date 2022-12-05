#ifndef DICIONARIO_AVL
#define DICIONARIO_AVL
#include "Verbete.hpp"
#include <iostream>
using namespace std;

#define MAX_VERBETES 4997

struct No{
    Verbete verbete;
    No *esquerda;
    No *direita;

    int fator_balanceamento;
};

class Dicionario_AVL{
    private:
        No* raiz;
        bool inseriu_primeiro = false;

    public:
        Dicionario_AVL();
        ~Dicionario_AVL();
        void deletarDicionario(No* NoAtual);
        No* obterRaiz();
        bool estavazio();
        bool estacheio();
        void inserir(Verbete verbete);
        void remover(Verbete verbete);
        void removerbusca(Verbete verbete, No*& noatual, bool& diminuiu);
        void deletarNo(No*& noatual, bool& diminuiu);
        void obterSucessor(Verbete& AlunoSucessor, No* temp);
        void buscar(Verbete& verbete, bool &cresceu);
        void imprimirpreordem(No* Noatual);
        void imprimiremordem(No* Noatual);
        void imprimirposordem(No* Noatual);

        // novos métodos:

        void rotacaodireita(No*& tree);
        void rotacaoesquerda(No*& tree);  
        void rotacaoesquerdadireita(No*& tree);
        void rotacaodireitaesquerda(No*& tree);
        void realizarotacao(No*& tree);
        void insererecursivo(No*& noatual, Verbete verbete, bool& cresceu);
        
};

#endif