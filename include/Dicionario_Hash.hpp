#ifndef DICIONARIO_HASH
#define DICIONARIO_HASH
#include "Verbete.hpp"
#include "memlog.h"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

class Dicionario_Hash{
    private:
        int FuncaoHash(Verbete verbete);
        
        //Quantos elementos, no maximo, vao ser adicionados
        static const int max_itens = 4997;

        static const int max_posicoes = 4995;

        //quantos itens foram adicionados no vetor
        int quantidade_itens;

        //vetor de elementos da classe verbete
        Verbete* estrutura;

    public:
        Dicionario_Hash();
        ~Dicionario_Hash();
        bool estacheio();
        int get_TamanhoAtual();
        void Inserir(Verbete verbete);
        void Deletar_Verbetes(ofstream *saida);
        void Buscar_Inserir(Verbete& verbete);
        void Imprimir(ofstream *saida);
        void Particao(int Esq, int Dir, int *i, int *j, Verbete *A);
        void Ordena_Recursivo(int Esq, int Dir, Verbete *A);
        void Ordena_Dicionario();
};

#endif