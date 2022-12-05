#include "Verbete.hpp"

Verbete::Verbete(char tipo, string verbete, string significado){
    this->tipo = tipo;
    this->verbete = verbete;
    this->significado = significado;
    inserir_significado(significado);
}

Verbete::Verbete(string verbete){
    this->verbete = verbete;
}

void Verbete::imprimir_significado(ofstream *saida){
    this->fila_significado.imprimir(&saida);
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