#include "Verbete.hpp"

Verbete::Verbete(char tipo, string verbete, string significado){
    //Descrição: Inicializa o verbete

    this->tipo = tipo;
    this->verbete = verbete;
    this->significado = significado;
    inserir_significado(significado);
}

Verbete::Verbete(){
    //Descrição: Inicializa o verbete da tabela hash

    this->verbete = "vazio";
    this->significado = " ";
    this->tipo = ' ';
}

Verbete::Verbete(string verbete){
    //Descrição: Inicializa o verbete

    this->verbete = verbete;
}

void Verbete::imprimir_significados(ofstream* saida){
    //Descrição: chama a função de impressão da fila de significados

    this->fila_significado.imprimir(saida);
}

void Verbete::inserir_significado(string significado){
    //Descrição: chama a função de inserção na fila de significados

    this->fila_significado.inserir(significado);
}

string Verbete::get_Verbete(){
    //Descrição: obtem o verbete do nó/posição atual

    return this->verbete;
}

string Verbete::get_Significado(){
    //Descrição: obtém o significado do nó/posição atual

    return this->significado;
}

char Verbete::get_Tipo(){
    //Descrição: obtém o tipo do nó/posição atual

    return this->tipo;
}

int Verbete::get_TamanhoFilaSignificados(){
    //Descrição: obtém o tamanho da fila de significados do nó/posição atual

    return fila_significado.get_tamanho();
}