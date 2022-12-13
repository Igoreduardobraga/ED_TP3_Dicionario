#include "Fila_Significado.hpp"

Fila_Significado::Fila_Significado(){
    //Descrição: Inicializa as variáveis da fila de significados

    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

Fila_Significado::~Fila_Significado(){

    // No_Fila* temp;
    // while (primeiro != NULL){
    //     temp = primeiro;
    //     primeiro = primeiro->proximo;
    //     delete temp;
    // }
    // ultimo = NULL;
}

bool Fila_Significado::estavazio(){
    //Descrição: Verifica se a fila de significados está vazia

    return (primeiro == NULL);
}

bool Fila_Significado::estacheio(){
    //Descrição: Verifica se a fila de significados está cheia

    No_Fila* temp;
    try{
        temp = new No_Fila;
        delete temp;
        return false;
    } catch(bad_alloc &exception){
        return true;
    }
}

void Fila_Significado::inserir(TipoItem significado){
    //Descrição: Insere um significado na fila

    if(significado!=""){
    if (estacheio()){
        cout << "A Fila esta cheia!\n";
        cout << "Nao foi possivel inserir este elemento!\n";
    } else{
        No_Fila* NoNovo = new No_Fila;
        NoNovo->significado = significado;
        NoNovo->proximo = NULL;
        if (primeiro == NULL){
            primeiro = NoNovo;
        } else{
            ultimo->proximo = NoNovo;
        }
        ultimo = NoNovo;
        tamanho++;
    }
    }
}

void Fila_Significado::remover(){
    //Descrição: remove um significado da fila

    if (estavazio()){
        cout << " ";
    } else{
        No_Fila* temp = primeiro;
        TipoItem item = primeiro->significado;
        primeiro = primeiro->proximo;
        if (primeiro == NULL){
            ultimo = NULL;
        }
        delete temp;
    }
}

void Fila_Significado::imprimir(ofstream* saida){
    //Descrição: Imprime a fila de significados

    No_Fila* temp = primeiro;
    unsigned short int cont = 1;

    while (temp != NULL){
        *saida << cont << ". ";
        *saida << temp->significado << endl;
        temp = temp->proximo;
        cont++;
    }
}

int Fila_Significado::get_tamanho(){
    //Descrição: Obtém o tamanho da fila de significados

    return tamanho;
}