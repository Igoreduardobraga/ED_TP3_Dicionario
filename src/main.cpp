#include <iostream>
#include <getopt.h>
#include <cstring>
#include "msgassert.h"
#include "memlog.h"
#include "Dicionario_AVL.hpp"
#include <fstream>
#include <string>
using namespace std;

string arquivo_entrada;
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
                arquivo_entrada = optarg;
                break;
            case 'o':
                arquivo_saida = optarg;
                break;
            case 't':
                implementacao = optarg;
            default:
                exit(1);
       }
    }

    // Verifica se o usuário digitou as entradas dos comandos -p -o e -i
    erroAssert(arquivo_entrada.size()>0, "main - nome de arquivo de entrada tem que ser definido");
    erroAssert(arquivo_saida.size()>0, "main - nome de arquivo de saida tem que ser definido");
    erroAssert(strlen(lognome)>0, "main - nome de arquivo de registro de acesso tem que ser definido");
}

string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

int main(int argc, char *argv[]){

    //AnalisaComando(argc,argv);

    // Inicia o registo de acesso
    //iniciaMemLog(lognome);

    // Se -l for encontrado no comando, ativa o registro de acesso. Caso não for encontrado, não ativa o registro de acesso
    // if(ativamem){
    //     ativaMemLog();
    // }
    // else{
    //     desativaMemLog();
    // }

    // if(implementacao=="avl"){

    // }
    // else{
        
    // }

    Dicionario_AVL alunos;
    //int opcao, imp;
    char palavra[30], significado[100];
    string palavra_conv, significado_conv;
    char tipo;
    int palavra_size;
    int significado_size;

    try{
    // ifstream entrada;
    // entrada.open(arquivo_entrada, std::ios::in);
    // if(!entrada.is_open()){
    //     throw "Nao foi possivel abrir o arquivo de entrada";
    // }
        ofstream saida;
        saida.open("saida.txt", ios::out);
        if(!saida.is_open()){
            throw "Nao foi possivel abrir o arquivo de saida";
        }

        FILE *entrada = fopen("entrada.txt","r");
        if(entrada==NULL){
            throw "Erro na abertura do arquivo de entrada";
        }

        do{
            fscanf(entrada,"%c %[^]] %[^\n]", &tipo, palavra,significado);
            palavra_size = sizeof(palavra)/sizeof(char);
            significado_size = sizeof(significado)/sizeof(char);
            palavra_conv = convertToString(palavra,palavra_size);
            significado_conv = convertToString(significado,significado_size);
            //palavra_conv.erase(0,1);

            saida << tipo << endl;
            Verbete verbete(tipo, palavra_conv, significado);
            if(alunos.estacheio())
                cout << "A arvore esta cheia!\n";
            else
                alunos.inserir(verbete);
        } while(!feof(entrada));

        fclose(entrada);
        

    } catch (const char *e){
        cout << "ERRO" << e << endl;
    }

    desativaMemLog();
}