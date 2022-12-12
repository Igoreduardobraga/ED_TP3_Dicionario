#include "Fila_Significado.hpp"

Fila_Significado::Fila_Significado() // Constructor
{
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

Fila_Significado::~Fila_Significado() // Destrutor
{
    // No_Fila* temp;
    // while (primeiro != NULL){
    //     temp = primeiro;
    //     primeiro = primeiro->proximo;
    //     delete temp;
    // }
    // ultimo = NULL;
}

bool Fila_Significado::estavazio() //isEmpty
{
    return (primeiro == NULL);
}

bool Fila_Significado::estacheio() //isFull
{
    No_Fila* temp;
    try{
        temp = new No_Fila;
        delete temp;
        return false;
    } catch(bad_alloc &exception){
        return true;
    }
}

void Fila_Significado::inserir(TipoItem significado) //enqueue //push
{
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

void Fila_Significado::remover() //dequeue //pop
{
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

void Fila_Significado::imprimir() //print
{
    ofstream saida;
    saida.open("saida.txt",ios::app);
    if(!saida){
        throw "Não foi possivel abrir o arquivo de saida";
    }
    No_Fila* temp = primeiro;
    unsigned short int cont = 1;

    while (temp != NULL){
        if(temp->significado=="")
            temp = temp->proximo;
        else{
        saida << cont << ". ";
        saida << temp->significado << endl;
        temp = temp->proximo;
        cont++;
        }
    }
}

int Fila_Significado::get_tamanho(){
    return tamanho;
}