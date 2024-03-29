#include "Dicionario_Hash.hpp"

int Dicionario_Hash::FuncaoHash(Verbete verbete){
    //Descrição: Transforma a chave de pesquisa em um endereço da tabela
    
    string palavra = verbete.get_Verbete();
    int tam = (palavra).length();
    unsigned int hash = 0;
    for(int i = 0; i<tam ; i++){
        hash += palavra[i]*(i+1);
    }
    return (hash % max_posicoes);
}

Dicionario_Hash::Dicionario_Hash(){
    //Descrição: Inicializa o contador de itens e o vetor onde os verbetes serão armazenados

    quantidade_itens = 0;
    estrutura = new Verbete[max_posicoes];
}

Dicionario_Hash::~Dicionario_Hash(){
    //Descrição: Destrói o dicionario

    delete [] estrutura;
}

bool Dicionario_Hash::estacheio(){
    //Descrição: Verifica se o vetor da tabela hash está cheio

    return (quantidade_itens == max_itens);
}

int Dicionario_Hash::get_TamanhoAtual(){
    //Descrição: Fornece o tamanho atual do vetor da tabela hash

    return quantidade_itens;
}

void Dicionario_Hash::Inserir(Verbete verbete){
    //Descrição: Insere verbetes no dicionario

    bool achou = false;
    int local = FuncaoHash(verbete);
    while(estrutura[local].get_Verbete() != "vazio" && estrutura[local].get_Verbete() != "removido"){
        if((estrutura[local].get_Verbete() == verbete.get_Verbete()) && (estrutura[local].get_Tipo() == verbete.get_Tipo())){
            estrutura[local].inserir_significado(verbete.get_Significado());
            LEMEMLOG((long int)(&(estrutura[local])), sizeof(Verbete), 0);
            achou = true;
            break;
        }
        else if((estrutura[local].get_Verbete() == verbete.get_Verbete()) && (estrutura[local].get_Tipo() != verbete.get_Tipo())){
            LEMEMLOG((long int)(&(estrutura[local])), sizeof(Verbete), 0);
            achou = false;
        }
        local = (local+1) % max_posicoes;
    }
    if(!achou){
        local = FuncaoHash(verbete);
        while(estrutura[local].get_Verbete() != "vazio" && estrutura[local].get_Verbete() != "removido"){
            LEMEMLOG((long int)(&(estrutura[local])), sizeof(Verbete), 0);
            local = (local+1) % max_posicoes;
        }
        estrutura[local] = verbete;
        LEMEMLOG((long int)(&(estrutura[local])), sizeof(Verbete), 0);
        quantidade_itens++;
    }
}

void Dicionario_Hash::Deletar_Verbetes(ofstream *saida){
    //Descrição: Deleta os verbetes que têm pelo menos um significado. Imprime aqueles que não têm significados
    for(int i=0 ; i<max_posicoes ; i++){
        if(estrutura[i].get_TamanhoFilaSignificados() >= 1){
            LEMEMLOG((long int)(&(estrutura[i])), sizeof(Verbete), 0);
            quantidade_itens--;
        }
        else{
            if(estrutura[i].get_Verbete() != "vazio" && estrutura[i].get_Verbete() != "removido"){
                *saida << estrutura[i].get_Verbete() << " (" << estrutura[i].get_Tipo() << ")" << endl;
                LEMEMLOG((long int)(&(estrutura[i])), sizeof(Verbete), 0);
            }
        }
    }
}

void Dicionario_Hash::Imprimir(ofstream *saida){
    //Descrição: Imprime o dicionario de verbetes e seus significados e tipos

    string aux;
    for(int i=0 ; i<max_posicoes ; i++){
        if(estrutura[i].get_Verbete() == estrutura[i+1].get_Verbete()){
            if((estrutura[i].get_Tipo()+estrutura[i].get_Verbete()) > (estrutura[i+1].get_Tipo()+estrutura[i+1].get_Verbete())){
                Verbete aux = estrutura[i];
                estrutura[i] = estrutura[i+1];
                estrutura[i+1] = aux;

                ESCREVEMEMLOG((long int)(&(estrutura[i])), sizeof(Verbete), 0);
                ESCREVEMEMLOG((long int)(&(estrutura[i+1])), sizeof(Verbete), 0);
                LEMEMLOG((long int)(&(estrutura[i])), sizeof(Verbete), 0);
                LEMEMLOG((long int)(&(estrutura[i+1])), sizeof(Verbete), 0);
            }
        }
        if(estrutura[i].get_Verbete() != "vazio" && estrutura[i].get_Verbete() != "removido"){
            *saida << estrutura[i].get_Verbete() << " (" << estrutura[i].get_Tipo() << ")" << endl;
            estrutura[i].imprimir_significados(saida);
            LEMEMLOG((long int)(&(estrutura[i])), sizeof(Verbete), 0);
        }
    }
}

void Dicionario_Hash::Particao(int Esq, int Dir, int *i, int *j, Verbete *A) {
    //Descricao: Realiza a partição do algoritmo QuickSort Recursivo

    Verbete x, w;
    *i = Esq; *j = Dir;
    x = A[(*i + *j)/2]; /* obtem o pivo x */
    do
    {
        while (x.get_Verbete() > A[*i].get_Verbete()){
            (*i)++;
        }
        while (x.get_Verbete() < A[*j].get_Verbete()){
            (*j)--;
        }
        if (*i <= *j)
        {
            w = A[*i]; 
            A[*i] = A[*j]; 
            A[*j] = w;

            (*i)++; 
            (*j)--;
        }
    } while (*i <= *j);
}

void Dicionario_Hash::Ordena_Recursivo(int Esq, int Dir, Verbete *A){
    //Descricao: Realiza a ordenação do algoritmo QuickSort Recursivo

    int i, j;
    Particao(Esq, Dir, &i, &j, A);
    if (Esq < j){
        Ordena_Recursivo(Esq, j, A);
    }
    if (i < Dir) {
        Ordena_Recursivo(i, Dir, A);
    }
}

void Dicionario_Hash::Ordena_Dicionario(){
    //Descricao: Chamada do algoritmo QuickSort Recursivo

    Ordena_Recursivo(0, max_posicoes-1, estrutura);
}