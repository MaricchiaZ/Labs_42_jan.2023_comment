/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:10:58 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/18 12:51:33 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * Its count height ot tree, and return the maximum of the height of the left and right
 * subtrees plus one. If the root is NULL, return -1.
 * 
 * @param root the root of the tree
 * 
 * @return The height of the tree.
 */
static int	height_tree(t_node *root) // mede a altura da árvore
{
	int	l, r;  // vai 

	if (root == NULL) // se chegar a um nó folha, n tem mais para onde ir
		return (-1); // retornamos a ultima soma 
	else{ // se deu certo
		l = height_tree(root->l) + 1; // chamamos recursivamente essa funçao para a esquerda
		r = height_tree(root->r) + 1; // chamamos recursivamente essa funçao para a direira
	}
	return (l > r) ? l : r; //confere qual lado deu o maior tamanho, e retorna a altura (maior caminho percorrido)
}

/**
 * It allocates memory for the dictionary. Creating the matrix dictionary with the size of ASCII thus optimizes program execution, because we have a direct access, by the ASCII value of the character.
 * 
 * @return A pointer to a pointer to a char.
 */
static char	**malloc_dic() // aloca a matriz dicionário
{
	char	**dictionary;
	int		i;
	
	dictionary = malloc(sizeof(char *) * 256); // a matriz conta com 265 ponteiros (para o acesso direto pelo valor ASCII)
	for (i = 0; i < 256; i++){
		dictionary[i] = calloc((enc.col + i), sizeof(char)); // e cada ponteiro interno cabe uma sequência de char com tamanho até a maior altura da árvore
	}
	return(dictionary); // retornamos o dicioário já alocado
}

/**
 * It takes a dictionary, a root node, a code_c, and a column number as parameters. It then creates two
 * strings, l and r, and copies the code_c into them. It then concatenates a 0 to l and a 1 to r. If
 * the root node is a leaf node, it copies the code_c into the dictionary at the index of the root
 * node's character. If the root node is not a leaf node, it recursively calls itself on the left and
 * right nodes of the root node, passing in the dictionary, the left and right nodes, and the l and r
 * strings
 * 
 * @param dictionary the dictionary we're building
 * @param root the root of the tree
 * @param code_c the code for the current node
 * @param col the length of the longest code in the dictionary
 */
void	make_dictionary(char ** dictionary, t_node *root, char *code_c, int col) //monta o dicionário, cada ponteiro interno na ordem ASCII recebe uma string com os 0 e 1 do caminho percorrido até a folha correspondente a esse caractere
{
	char l[col], r[col]; // criamos duas strings auxiliares
	
	if (root->l == NULL && root->r == NULL) // se chegamos a um nó-folha
		strcpy(dictionary[root->c], code_c); // salvamos a string no dicionário
	else{ // se nao for um nó-folha
		strcpy(l, code_c); // a string auxiliar l recebe o caminho já percorrido até aqui
		strcpy(r, code_c); // a string auxiliar r recebe o caminho já percorrido até aqui

		strcat(l, "0");  // a string auxiliar l ganha mais um 0 ao final da sua string
		strcat(r, "1");  // a string auxiliar r ganha mais um 0 ao final da sua string 
		make_dictionary(dictionary, root->l, l, col); // tenta recursivamente ir pra esquerda
		make_dictionary(dictionary, root->r, r, col); // tenta recursivamente ir pra direita 
	}
}

/**
 * It takes the tree height and makes a dictionary out of it
 */
void	prepare_dictionary() // função que monta o dicionário para o AH
{
	printf("Making dictionary...\n"); // avisamos que iniciamos essa etapa
	enc.col = height_tree(enc.tree); //mede a distância do nó raiz- até o nó folha mais distante// o dicionário é uma matriz, 256 linhas para ser uma matriz de acesso direto, e seu número de colunas depende da altura da árvore
	enc.dictionary = malloc_dic(); // alocamos o dicionário
	make_dictionary(enc.dictionary, enc.tree, "", enc.col); // montamos então o dicionário, agora que ele já está alocado, em cada ponteiro interno 
}
