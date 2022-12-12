#include "Dicionario_AVL.hpp"
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

void Dicionario_AVL::Destruir_Dicionario(No* Noatual)
{
	if (Noatual != NULL){
		Destruir_Dicionario(Noatual->esquerda);

		Destruir_Dicionario(Noatual->direita);

		delete Noatual;
	}
}

int Dicionario_AVL::altura(No *N)
{
	if (N == NULL)
		return 0;
	return N->altura;
}

int Dicionario_AVL::max(int a, int b)
{
	return (a > b)? a : b;
}

No* Dicionario_AVL::NovoNo(Verbete verbete)
{
	No* node = new No();
	node->verbete = verbete;
	node->esquerda = NULL;
	node->direita = NULL;
	node->altura = 1;
					
	return(node);
}

No *Dicionario_AVL::Rotacao_Direita(No *y)
{
	No *x = y->esquerda;
	No *T2 = x->direita;

	x->direita = y;
	y->esquerda = T2;

	y->altura = max(altura(y->esquerda),
					altura(y->direita)) + 1;
	x->altura = max(altura(x->esquerda),
					altura(x->direita)) + 1;

	return x;
}

No *Dicionario_AVL::Rotacao_Esquerda(No *x)
{
	No *y = x->direita;
	No *T2 = y->esquerda;

	y->esquerda = x;
	x->direita = T2;

	x->altura = max(altura(x->esquerda),
					altura(x->direita)) + 1;
	y->altura = max(altura(y->esquerda),
					altura(y->direita)) + 1;

	return y;
}

int Dicionario_AVL::get_balanceamento(No *N)
{
	if (N == NULL)
		return 0;
	return altura(N->esquerda) - altura(N->direita);
}

No* Dicionario_AVL::inserir(No* node, Verbete verbete)
{
	if (node == NULL)
		return(NovoNo(verbete));

    if((verbete.get_Verbete() == node->verbete.get_Verbete()) && (verbete.get_Tipo() == node->verbete.get_Tipo())){
        node->verbete.inserir_significado(verbete.get_Significado());
    }
	else if((verbete.get_Verbete() == node->verbete.get_Verbete()) && (verbete.get_Tipo() != node->verbete.get_Tipo())){
		node->direita = inserir(node->direita, verbete);
	}
	else if (verbete.get_Verbete() < node->verbete.get_Verbete())
		node->esquerda = inserir(node->esquerda, verbete);
	else if (verbete.get_Verbete() > node->verbete.get_Verbete())
		node->direita = inserir(node->direita, verbete);
    else{
        return node;
    }
    
	node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

	int balance = get_balanceamento(node);

	if (balance > 1 && verbete.get_Verbete() < node->esquerda->verbete.get_Verbete())
		return Rotacao_Direita(node);

	
	if (balance < -1 && verbete.get_Verbete() > node->direita->verbete.get_Verbete())
		return Rotacao_Esquerda(node);

	if (balance > 1 && verbete.get_Verbete() > node->esquerda->verbete.get_Verbete())
	{
		node->esquerda = Rotacao_Esquerda(node->esquerda);
		return Rotacao_Direita(node);
	}

	if (balance < -1 && verbete.get_Verbete() < node->direita->verbete.get_Verbete())
	{
		node->direita = Rotacao_Direita(node->direita);
		return Rotacao_Esquerda(node);
	}

	return node;
}


No * Dicionario_AVL::minValueNode(No* node)
{
	No* current = node;

	while (current->esquerda != NULL)
		current = current->esquerda;

	return current;
}

No* Dicionario_AVL::Remover_Verbetes(No* raiz)
{
	if(raiz!=NULL){
		if(raiz->verbete.get_TamanhoFilaSignificados() >= 1){
			Remover_Verbetes(raiz->direita);

			Remover_Verbetes(raiz->esquerda);
		}
		if( (raiz->esquerda == NULL) || (raiz->direita == NULL) )
		{
			No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

			if (temp == NULL)
			{
				temp = raiz;
				raiz = NULL;
			}
			else
			*raiz = *temp;

			//free(temp);
		}
		else
		{
			No* temp = minValueNode(raiz->direita);

			raiz->verbete = temp->verbete;

			raiz->direita = Remover_Verbetes(raiz->direita);
		}
	}

	if (raiz == NULL)
	return raiz;

	raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

	int balance = get_balanceamento(raiz);

	if (balance > 1 && get_balanceamento(raiz->esquerda) >= 0)
		return Rotacao_Direita(raiz);

	if (balance > 1 && get_balanceamento(raiz->esquerda) < 0)
	{
		raiz->esquerda = Rotacao_Esquerda(raiz->esquerda);
		return Rotacao_Direita(raiz);
	}

	if (balance < -1 && get_balanceamento(raiz->direita) <= 0)
		return Rotacao_Esquerda(raiz);

	if (balance < -1 && get_balanceamento(raiz->direita) > 0)
	{
		raiz->direita = Rotacao_Direita(raiz->direita);
		return Rotacao_Esquerda(raiz);
	}
	else
		return raiz;
}

void Dicionario_AVL::Imprimir_Dicionario(No *noatual, ofstream *saida)
{
	//Imprime o verbete, seu tipo e significado
	if(noatual != NULL)
	{
		Imprimir_Dicionario(noatual->esquerda, saida);
        *saida << noatual->verbete.get_Verbete() << " (" << noatual->verbete.get_Tipo() << ")" << endl;
        noatual->verbete.imprimir_significados();

		Imprimir_Dicionario(noatual->direita,saida);
	}
}

No* Dicionario_AVL::PesquisaRecursivo(No *no, string chave) {
    if (no == NULL) {
        //return ;
    }
    if (chave < no->verbete.get_Verbete())
        return PesquisaRecursivo(no->esquerda, chave);
    else if (chave > no->verbete.get_Verbete())
        return PesquisaRecursivo(no->direita, chave);
    else
        return no;
}