#include "Verbete.hpp"

Verbete::Verbete(char tipo, string verbete, string significado){
    this->tipo = tipo;
    this->verbete = verbete;
    this->significado = significado;
    inserir_significado(significado);
}

Verbete::Verbete(){
    this->verbete = "vazio";
    this->significado = " ";
    this->tipo = ' ';
}

Verbete::Verbete(string verbete){
    this->verbete = verbete;
}

void Verbete::imprimir_significados(){
    this->fila_significado.imprimir();
}

void Verbete::inserir_significado(string significado){
    this->fila_significado.inserir(significado);
}

string Verbete::get_Verbete(){
    return this->verbete;
}

string Verbete::get_Significado(){
    return this->significado;
}

char Verbete::get_Tipo(){
    return this->tipo;
}

int Verbete::get_TamanhoFilaSignificados(){
    return fila_significado.get_tamanho();
}