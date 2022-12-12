#ifndef DICIONARIO_HASH
#define DICIONARIO_HASH
#include "Verbete.hpp"
#include <iostream>
#include <cstring>

using namespace std;

class Dicionario_Hash{
    private:
        int FuncaoHash(Verbete verbete);
        
        //Quantos elementos, no maximo, vao ser adicionados
        static const int max_itens = 3997;

        static const int max_posicoes = 3995;

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
        Verbete Buscar(Verbete& verbete);
        void Imprimir();
};

#endif