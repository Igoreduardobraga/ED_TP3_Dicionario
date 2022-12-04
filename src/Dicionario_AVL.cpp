#include <iostream>
#include <cstddef>
#include "Dicionario_AVL.hpp"

using namespace std;

Dicionario_AVL::Dicionario_AVL()
{
    raiz = NULL;
}

Dicionario_AVL::~Dicionario_AVL()
{
    deletarDicionario(raiz);
}

void Dicionario_AVL::deletarDicionario(No* Noatual)
{
    if (Noatual != NULL){
        deletarDicionario(Noatual->esquerda);

        deletarDicionario(Noatual->direita);

        delete Noatual;
    }
}

No* Dicionario_AVL::obterRaiz()
{
    return raiz;
}

bool Dicionario_AVL::estavazio()
{
    return (raiz == NULL);
}

bool Dicionario_AVL::estacheio()
{
    try{
        No* temp = new No;
        delete temp;
        return false;
    } catch(bad_alloc &exception){
        return true;
    }
}

void Dicionario_AVL::inserir(Verbete verbete){
    bool cresceu;
    buscar(verbete, raiz, cresceu);
    //insererecursivo(raiz, verbete, cresceu);
}

void Dicionario_AVL::insererecursivo(No*& noatual, Verbete verbete, bool& cresceu)
{
    if (noatual == NULL) {
        noatual = new No;
        noatual->direita = NULL;
        noatual->esquerda = NULL;
        noatual->verbete = verbete;
        noatual->fator_balanceamento = 0;
        cresceu = true;
        return;
    }  
    if (verbete.get_Verbete() < noatual->verbete.get_Verbete()) {
        insererecursivo(noatual->esquerda, verbete, cresceu);
        if (cresceu){
            noatual->fator_balanceamento-=1;   
        } 
    } else {
        insererecursivo(noatual->direita, verbete, cresceu);
        if (cresceu){
            noatual->fator_balanceamento+=1;
        }    
    } 
    realizarotacao(noatual);

    if (cresceu && noatual->fator_balanceamento == 0){
        cresceu = false;
    }
}

void Dicionario_AVL::remover(Verbete verbete)
{
    bool diminuiu;
    removerbusca(verbete, raiz, diminuiu);
}

void Dicionario_AVL::removerbusca(Verbete verbete, No*& noatual, bool& diminuiu)
{
    if (verbete.get_Verbete() < noatual->verbete.get_Verbete()){
        removerbusca(verbete, noatual->esquerda, diminuiu);
        if (diminuiu){
            noatual->fator_balanceamento+=1;
        }
    } else if (verbete.get_Verbete() > noatual->verbete.get_Verbete()){
        removerbusca(verbete, noatual->direita, diminuiu);
        if (diminuiu){
            noatual->fator_balanceamento-=1;
        }
    } else{
        deletarNo(noatual, diminuiu);
    }
    if (noatual != NULL){
        realizarotacao(noatual);
        if (diminuiu && noatual->fator_balanceamento != 0){
            diminuiu = false;
        }
    }
}

void Dicionario_AVL::deletarNo(No*& noatual, bool& diminuiu)
{
    No* temp = noatual;
    if (noatual->esquerda == NULL){
        noatual = noatual->direita;
        diminuiu = true;
        delete temp;
    } else if (noatual->direita == NULL){
        noatual = noatual->esquerda;
        diminuiu = true;
        delete temp;
    } else{
        Verbete AlunoSucessor;
        obterSucessor(AlunoSucessor, noatual);
        noatual->verbete = AlunoSucessor;
        removerbusca(AlunoSucessor, noatual->direita, diminuiu);
        if (diminuiu){
            noatual->fator_balanceamento-=1;
        }
    }
}

void Dicionario_AVL::obterSucessor(Verbete& AlunoSucessor, No* temp)
{
    temp = temp->direita;
    while (temp->esquerda != NULL){
        temp = temp->esquerda;
    }
    AlunoSucessor = temp->verbete;
}

void Dicionario_AVL::buscar(Verbete& verbete, No*& raiz, bool &cresceu)
{
    No* noatual = raiz;
    while (noatual != NULL){
        if (verbete.get_Verbete() < noatual->verbete.get_Verbete()){
            noatual = noatual->esquerda;
        } else if (verbete.get_Verbete() > noatual->verbete.get_Verbete()){
            noatual = noatual->direita;
        } else if(verbete.get_Verbete() == noatual->verbete.get_Verbete()){
            verbete = noatual->verbete;
            noatual->verbete.inserir_significado(verbete.get_Significado());
            break;
        }
        else
            insererecursivo(raiz, verbete, cresceu);
    }
}

void Dicionario_AVL::imprimirpreordem(No* Noatual)
{
    if (Noatual != NULL){
        //cout << Noatual->verbete.obterNome() << ": ";
        cout << Noatual->verbete.get_Verbete() << endl;

        imprimirpreordem(Noatual->esquerda);

        imprimirpreordem(Noatual->direita);
    }
}

void Dicionario_AVL::imprimiremordem(No* Noatual)
{
    if (Noatual != NULL){
        imprimiremordem(Noatual->esquerda);

        //cout << Noatual->verbete.obterNome() << ": ";
        cout << Noatual->verbete.get_Verbete() << endl;
        Noatual->verbete.imprimir_significado();

        imprimiremordem(Noatual->direita);            
    }
}

void Dicionario_AVL::imprimirposordem(No* Noatual)
{
    if (Noatual != NULL){
        imprimirposordem(Noatual->esquerda);

        imprimirposordem(Noatual->direita);

        //cout << Noatual->verbete.obterNome() << ": ";
        cout << Noatual->verbete.get_Verbete() << endl;            
    }
}

void Dicionario_AVL::rotacaodireita(No*& pai) //novo
{
    No* novopai = pai->esquerda;
    pai->esquerda = novopai->direita;
    novopai->direita = pai;
    pai = novopai;
}

void Dicionario_AVL::rotacaoesquerda(No*& pai) //novo
{
    No* novopai = pai->direita;
    pai->direita = novopai->esquerda;
    novopai->esquerda = pai;
    pai = novopai;
}

void Dicionario_AVL::rotacaoesquerdadireita(No*& pai)
{
    No* filho = pai->esquerda;
    rotacaoesquerda(filho);
    pai->esquerda = filho;
    rotacaodireita(pai);
}


void Dicionario_AVL::rotacaodireitaesquerda(No*& pai)
{
    No* filho = pai->direita;
    rotacaodireita(filho);
    pai->direita = filho;
    rotacaoesquerda(pai);
}


void Dicionario_AVL::realizarotacao(No*& pai)
{
    No* filho;
    No* neto; // Caso precise da rotação dupla

    if (pai->fator_balanceamento == -2){ //rotaciona para a direita

    filho = pai->esquerda;

    if (filho->fator_balanceamento == -1){ // Simples para a direita
        pai->fator_balanceamento = 0;
        filho->fator_balanceamento = 0;
        rotacaodireita(pai);
    } else if (filho->fator_balanceamento == 0){ // Simples para a direita
        pai->fator_balanceamento = -1;
        filho->fator_balanceamento = 1;
        rotacaodireita(pai);
    } else if (filho->fator_balanceamento == 1){ // Rotação dupla
        neto = filho->direita;
        if (neto->fator_balanceamento == -1){
            pai->fator_balanceamento = 1;
            filho->fator_balanceamento = 0;
        } else if (neto->fator_balanceamento == 0){
            pai->fator_balanceamento = 0;
            filho->fator_balanceamento = 0;                
        } else if (neto->fator_balanceamento == 1){
            pai->fator_balanceamento = 0;
            filho->fator_balanceamento = -1;                
        }
        neto->fator_balanceamento = 0; 
        rotacaodireitaesquerda(pai);            
    }



    } else if(pai->fator_balanceamento == 2){ //rotaciona para a esquerda
        filho = pai->direita;
        if (filho->fator_balanceamento == 1) { // Simples para a esquerda
            pai->fator_balanceamento = 0;
            filho->fator_balanceamento = 0;
            rotacaoesquerda(pai);
        } else if (filho->fator_balanceamento == 0){ // Simples para a esquerda         
            pai->fator_balanceamento = 1;
            filho->fator_balanceamento = -1;
            rotacaoesquerda(pai);
        } else if (filho->fator_balanceamento == -1){ // Rotacao dupla
            neto = filho->esquerda;
            if (neto->fator_balanceamento == -1){
                pai->fator_balanceamento =  0;
                filho->fator_balanceamento = 1; 
            } else if (neto->fator_balanceamento == 0){
                pai->fator_balanceamento =  0;
                filho->fator_balanceamento = 0; 
            } else if (neto->fator_balanceamento == 1){
                pai->fator_balanceamento =  -1;
                filho->fator_balanceamento = 0; 
            }
            neto->fator_balanceamento = 0;
            rotacaodireitaesquerda(pai);
        }
    }
}                  