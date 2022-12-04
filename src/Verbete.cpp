#include "Verbete.hpp"

Verbete::Verbete(char tipo, string verbete, string significado){
    this->tipo = tipo;
    this->verbete = verbete;
    this->significado.inserir(significado);
}

Verbete::Verbete(string verbete){
    this->verbete = verbete;
}

void Verbete::imprimir_significado(){
    this->significado.imprimir();
}

string Verbete::get_Verbete(){
    return this->verbete;
}