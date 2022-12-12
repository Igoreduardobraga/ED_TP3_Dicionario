#include "Dicionario_Hash.hpp"

int Dicionario_Hash::FuncaoHash(Verbete verbete){
    string palavra = verbete.get_Verbete();
    int tam = (palavra).length();
    unsigned int hash = 0;
    for(int i = 0; i<tam ; i++){
        hash += palavra[i]*(i+1);
    }
    return (hash % max_posicoes);
}

Dicionario_Hash::Dicionario_Hash(){
    quantidade_itens = 0;
    estrutura = new Verbete[max_posicoes];
}

Dicionario_Hash::~Dicionario_Hash(){
    delete [] estrutura;
}

bool Dicionario_Hash::estacheio(){
    return (quantidade_itens == max_itens);
}

int Dicionario_Hash::get_TamanhoAtual(){
    return quantidade_itens;
}

void Dicionario_Hash::Inserir(Verbete verbete){
    Verbete aux;
    aux = Buscar(verbete);
    if(aux.get_Verbete() != "vazio" && aux.get_Verbete() != "removido"){
        aux.inserir_significado(verbete.get_Significado());
    }
    else{
        int local = FuncaoHash(verbete);
        while(estrutura[local].get_Verbete() != "vazio" && estrutura[local].get_Verbete() != "removido"){
            local = (local+1) % max_posicoes;
        }
        estrutura[local] = verbete;
        quantidade_itens++;
    }
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
        local = (local+1) % max_posicoes;
    }
    if(!teste){
        cout << "Elemento nao encontrado" << endl;
    }
}
Verbete Dicionario_Hash::Buscar(Verbete& verbete){
    Verbete temp;
    int local = FuncaoHash(verbete);
    Verbete aux = estrutura[local];
    while(estrutura[local].get_Verbete() != "vazio"){
        if(estrutura[local].get_Verbete() == verbete.get_Verbete()){
            temp = estrutura[local];
            break;
        }
        local = (local+1) % max_posicoes;
    }
    return temp;
}

void Dicionario_Hash::Imprimir(){
    for(int i=0 ; i<max_posicoes ; i++){
        if(estrutura[i].get_Verbete() != "vazio" && estrutura[i].get_Verbete() != "removido"){
            cout << estrutura[i].get_Verbete() << " (" << estrutura[i].get_Tipo() << ")" << endl;
            estrutura[i].imprimir_significados();
        }
    }
}