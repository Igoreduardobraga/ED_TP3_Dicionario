#ifndef DICIONARIO_HASH
#define DICIONARIO_HASH
#include "Verbete.hpp"
#include <iostream>
#include <cstring>

using namespace std;

//Quantos elementos, no maximo, vao ser adicionados
#define MAX_ITENS 4997

#define MAX_POSICOES 1000

class Dicionario_Hash{
    private:
        int FuncaoHash(Verbete verbete);

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
        void Deletar(Verbete verbete);
        void Buscar(Verbete& verbete, bool &achou);
        void Imprimir();
};

#endif