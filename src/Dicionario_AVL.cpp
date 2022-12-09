#include "Dicionario_AVL.hpp"
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

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

/* Helper function that allocates a
new node with the given verbete.get_Verbete() and
NULL esquerda and direita pointers. */
No* Dicionario_AVL::NovoNo(string verbete)
{
	No* node = new No();
	node->verbete.set_Verbete(verbete);
	node->esquerda = NULL;
	node->direita = NULL;
	node->altura = 1; // new node is initially
					// added at leaf
	return(node);
}

No *Dicionario_AVL::Rotacao_Direita(No *y)
{
	No *x = y->esquerda;
	No *T2 = x->direita;

	// Perform rotation
	x->direita = y;
	y->esquerda = T2;

	// Update heights
	y->altura = max(altura(y->esquerda),
					altura(y->direita)) + 1;
	x->altura = max(altura(x->esquerda),
					altura(x->direita)) + 1;

	// Return new raiz
	return x;
}

No *Dicionario_AVL::Rotacao_Esquerda(No *x)
{
	No *y = x->direita;
	No *T2 = y->esquerda;

	// Perform rotation
	y->esquerda = x;
	x->direita = T2;

	// Update heights
	x->altura = max(altura(x->esquerda),
					altura(x->direita)) + 1;
	y->altura = max(altura(y->esquerda),
					altura(y->direita)) + 1;

	// Return new raiz
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
		return(NovoNo(verbete.get_Verbete()));

    if(verbete.get_Verbete() == node->verbete.get_Verbete()){
        node->verbete.inserir_significado(verbete.get_Significado());
    }
	else if (verbete.get_Verbete() < node->verbete.get_Verbete())
		node->esquerda = inserir(node->esquerda, verbete.get_Verbete());
	else if (verbete.get_Verbete() > node->verbete.get_Verbete())
		node->direita = inserir(node->direita, verbete.get_Verbete());
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

No* Dicionario_AVL::DeletarNo(No* raiz, Verbete verbete)
{
	
	if (raiz == NULL)
		return raiz;

	if ( verbete.get_Verbete() < raiz->verbete.get_Verbete() )
		raiz->esquerda = DeletarNo(raiz->esquerda, verbete);

	else if( verbete.get_Verbete() > raiz->verbete.get_Verbete() )
		raiz->direita = DeletarNo(raiz->direita, verbete.get_Verbete());

	else
	{
		// node with only one child or no child
		if( (raiz->esquerda == NULL) ||
			(raiz->direita == NULL) )
		{
			No *temp = raiz->esquerda ?
						raiz->esquerda :
						raiz->direita;

			// No child case
			if (temp == NULL)
			{
				temp = raiz;
				raiz = NULL;
			}
			else // One child case
			*raiz = *temp; // Copy the contents of
						// the non-empty child
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder
			// successor (smallest in the direita subtree)
			No* temp = minValueNode(raiz->direita);

			// Copy the inorder successor's
			// data to this node
			raiz->verbete.get_Verbete() = temp->verbete.get_Verbete();

			// Delete the inorder successor
			raiz->direita = DeletarNo(raiz->direita,
									temp->verbete.get_Verbete());
		}
	}

	// If the tree had only one node
	// then return
	if (raiz == NULL)
	return raiz;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	raiz->altura = 1 + max(altura(raiz->esquerda),
						altura(raiz->direita));

	// STEP 3: GET THE BALANCE FACTOR OF
	// THIS NODE (to check whether this
	// node became unbalanced)
	int balance = get_balanceamento(raiz);

	// If this node becomes unbalanced,
	// then there are 4 cases

	// Left Left Case
	if (balance > 1 &&
		get_balanceamento(raiz->esquerda) >= 0)
		return Rotacao_Direita(raiz);

	// Left Right Case
	if (balance > 1 &&
		get_balanceamento(raiz->esquerda) < 0)
	{
		raiz->esquerda = Rotacao_Esquerda(raiz->esquerda);
		return Rotacao_Direita(raiz);
	}

	// Right Right Case
	if (balance < -1 &&
		get_balanceamento(raiz->direita) <= 0)
		return Rotacao_Esquerda(raiz);

	// Right Left Case
	if (balance < -1 &&
		get_balanceamento(raiz->direita) > 0)
	{
		raiz->direita = Rotacao_Direita(raiz->direita);
		return Rotacao_Esquerda(raiz);
	}

	return raiz;
}

// A utility function to print preorder
// traversal of the tree.
// The function also prints altura
// of every node
void Dicionario_AVL::Imprimir_Dicionario(No *noatual, ofstream *saida)
{
	if(noatual != NULL)
	{
		Imprimir_Dicionario(noatual->esquerda, saida);
        *saida << noatual->verbete.get_Verbete() << endl;
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