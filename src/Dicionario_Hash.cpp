#include "Dicionario_Hash.hpp"

int Dicionario_Hash::FuncaoHash(Verbete verbete){
    string palavra = verbete.get_Verbete();
    int tam = (verbete.get_Verbete()).length();
    unsigned int hash = 0;
    for(int i = 0; i<tam ; i++){
        hash += palavra[i]*(i+1);
    }
    return (hash % MAX_POSICOES);
}

Dicionario_Hash::Dicionario_Hash(){
    quantidade_itens = 0;
    estrutura = new Verbete[MAX_POSICOES];
}

Dicionario_Hash::~Dicionario_Hash(){
    delete [] estrutura;
}

bool Dicionario_Hash::estacheio(){
    return (quantidade_itens == MAX_ITENS);
}

int Dicionario_Hash::get_TamanhoAtual(){
    return quantidade_itens;
}

void Dicionario_Hash::Inserir(Verbete verbete){
    int local = FuncaoHash(verbete);
    while(estrutura[local].get_Verbete() != "vazio"){
        local = (local+1) % MAX_POSICOES;
    }
    estrutura[local] = verbete;
    quantidade_itens++;
}

void Dicionario_Hash::Deletar(Verbete verbete){
    int local = FuncaoHash(verbete);
    bool teste = false;
    while(estrutura[local].get_Verbete() != "vazio"){
        if(estrutura[local].get_Verbete() == verbete.get_Verbete()){
            estrutura[local] = Verbete(' ', "removido", " ");
            teste = true;
            quantidade_itens--;
            break;
        }
        local = (local+1) % MAX_POSICOES;
    }
    if(!teste){
        cout << "Elemento nao encontrado" << endl;
    }
}
void Dicionario_Hash::Buscar(Verbete& verbete, bool &achou){
    int local = FuncaoHash(verbete);
    Verbete aux = estrutura[local];
    while(estrutura[local].get_Verbete() != "vazio"){
        if(estrutura[local].get_Verbete() == verbete.get_Verbete()){
            achou = true;
            verbete = estrutura[local];
            break;
        }
        local = (local+1) % MAX_POSICOES;
    }
    
}
void Dicionario_Hash::Imprimir(){
    for(int i=0 ; i<MAX_POSICOES ; i++){
        cout << i << ":" << estrutura[i].get_Verbete() << " ";
        estrutura[i].imprimir_significados();
    }
}