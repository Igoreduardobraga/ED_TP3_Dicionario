#include <iostream>
#include <getopt.h>
#include <cstring>
#include "msgassert.h"
#include "memlog.h"
#include "Dicionario_AVL.hpp"
#include "Dicionario_Hash.hpp"
#include <fstream>
#include <string>
using namespace std;

char arquivo_entrada[100];
string arquivo_saida;
string implementacao;
bool ativamem;
char lognome[100];

void AnalisaComando(int argc, char ** argv){
    // Descrição: analisa a linha de comando a partir do arc e agrv

    // Variavel externa do getopt
    extern char *optarg;

    // Inicializa ativamem com false. caso haja -l no comando ativamem torna-se verdadeira
    ativamem = 0;

    // Variavel auxiliar
    int opcao;

    // Inicializa lognome
    lognome[0] = 0;

    while ((opcao = getopt(argc, argv, "p:li:o:t:")) != EOF){
       switch(opcao) {
            case 'p':
                strcpy(lognome,optarg);
                break;
            case 'l':
                ativamem = 1;
                break;
            case 'i':
                strcpy(arquivo_entrada,optarg);
                break;
            case 'o':
                arquivo_saida = optarg;
                break;
            case 't':
                implementacao = optarg;
                break;
            default:
                exit(1);
                break;
       }
    }

    // Verifica se o usuário digitou as entradas dos comandos -p -o e -i
    erroAssert(strlen(arquivo_entrada)>0, "main - nome de arquivo de entrada tem que ser definido");
    erroAssert(arquivo_saida.size()>0, "main - nome de arquivo de saida tem que ser definido");
    erroAssert(strlen(lognome)>0, "main - nome de arquivo de registro de acesso tem que ser definido");
}

int main(int argc, char *argv[]){

    AnalisaComando(argc,argv);

    //Inicia o registo de acesso
    iniciaMemLog(lognome);

    //Se -l for encontrado no comando, ativa o registro de acesso. Caso não for encontrado, não ativa o registro de acesso
    if(ativamem){
        ativaMemLog();
    }
    else{
        desativaMemLog();
    }

    try{

    FILE *entrada = fopen(arquivo_entrada,"r");
    if(entrada==NULL){
        throw "Erro na abertura do arquivo de entrada";
    }

    ofstream saida;
    saida.open(arquivo_saida,ios::app);
    if(!saida){
        throw "Não foi possivel abrir o arquivo de saida";
    }

    // Implementação utilizando árvore AVL
    if(implementacao=="avl"){
        Dicionario_AVL dicionario_avl;
        char palavra[30], significado[100];
        char tipo;
        No *raiz = NULL;

        do{
            fscanf(entrada,"%c %[^]] %[^\n]%*c", &tipo, palavra, significado);
            string palavra_conv(palavra);
            string significado_conv(significado);
            palavra_conv.erase(0,1);
            significado_conv.erase(0,2);
            Verbete verbete(tipo, palavra_conv, significado_conv);
            raiz = dicionario_avl.inserir(raiz,verbete);
        } while(!feof(entrada));

        dicionario_avl.Imprimir_Dicionario(raiz,&saida);

        //Remove os verbetes que têm pelo menos um significado
        raiz = dicionario_avl.Remover_Verbetes(raiz);

        dicionario_avl.Destruir_Dicionario(raiz);
    }
    // Implementação utilizando tabela hash
    else{
        Dicionario_Hash dicionario_hash;
        char palavra[30], significado[100];
        char tipo;

        do{
            fscanf(entrada,"%c %[^]] %[^\n]%*c", &tipo, palavra, significado);
            string palavra_conv(palavra);
            string significado_conv(significado);
            palavra_conv.erase(0,1);
            significado_conv.erase(0,2);
            Verbete verbete(tipo, palavra_conv, significado_conv);
            dicionario_hash.Inserir(verbete);
        } while(!feof(entrada));

        // Ordena o dicionario utilizando o algoritmo quicksort
        dicionario_hash.Ordena_Dicionario();

        dicionario_hash.Imprimir(&saida);

        // Deleta os verbetes que possuem pelo menos 1 significado e imprime aqueles que não possuem
        dicionario_hash.Deletar_Verbetes(&saida);
    }

    fclose(entrada);

    } catch (const char *e){
            cout << "ERRO" << e << endl;
    }

    

    //desativaMemLog();
}