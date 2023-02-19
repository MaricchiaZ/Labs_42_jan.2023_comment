/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:59:25 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/17 18:34:09 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It initializes the list
 */
void	init_list() // função que iniciaiza a lista lincada que é necessária para o AH
{
	enc.list = calloc(1, sizeof(t_list)); //a variável que receberá a lista é alocada
	enc.list->start = NULL; //o ponteiro start é inicializado
	enc.list->size = 0; // o tamanho da lista é inicializado
}

/**
 * It inserts a node in the list in ascending order of frequency
 * 
 * @param node the node to be inserted
 */
void	insert_sort(t_node *node) // insere o nó recebido na lista, levando em conta a variável frequência do nó
{
	t_node	*aux; // cria um nó auxiliar 

	if (enc.list->start == NULL){ // se a lista ainda estiver vazia
		enc.list->start = node; // esse nó passado será o primeiro nó da lista
	}
	else if (node->freq < enc.list->start->freq){ // se a sua frequência for menor do que a inicial
		node->next = enc.list->start; // o ponteiro next do nó recebe o endereço do primeiro da lista (o ponteiro next desse novo nó vai apontar pro primeiro da lista)
		enc.list->start = node; // e o ponteiro da lista agora aponta pro novo nó
	}
	else { // mas se não for maior
		aux = enc.list->start; //salvamos o início da lista num nó temporário
		while (aux->next && aux->next->freq <= node->freq) // e percorremos a lista enquanto a frequência for menor ou igual
			aux = aux->next; //  // o nó aulixiar vai recebendo o ponteiro pro próximo nó (e assim percorremos a lista)
		node->next = aux->next; // o ponteiro do nó que queremos inserir vai apontar pro próximo da lista 
		aux->next = node; // e inserimos ele na lista 
	}
	enc.list->size++; // acrescentamos uma unidade no tamanho da lista 
}

/**
 * It removes the first node of the list and returns it
 * 
 * @return A pointer to a node.
 */
t_node	*remove_init_node() // remove o primeiro nó da lista
{
	t_node	*aux = NULL; // criamos um nó auxiliar e inicialiamos com NULL

	if (enc.list->start){ // se existir algo na lista
		aux = enc.list->start; // aux recebe o ponteito pra lista
		enc.list->start = aux->next; // ponteiro pra lista recebe o segundo nó
		aux->next = NULL; // o ponteiro next do nó auxiliar é zerado
		enc.list->size--; //tamanho da lista perde 1 de valor
	}
	return (aux); // retornamos esse nó "solto"
}

/**
 * It creates a linked list of nodes, each node containing a character and its frequency
 */
void	prepare_list() // faz uma lista encadeada ordenada com os caracteres presentes na tabela, a lista é preenchida em ordem do menos frequente para o mais frequente
{
	printf("Making sorted frequency list...\n"); //  avisamos que iniciamos a Lista de Frequência Ordenada
	t_node	*new; // declaramos que iremos usar uma struct t_node chamada new

	bzero(enc.list, sizeof(t_list)); // passamos a bzero na lista
	for (int i=0; i < 256; i++){  // enquanto não percorrermos toda a tabela de frequência
		if (enc.freq_tab[i] > 0){ // se aquela posição da tabela tiver conteúdo
			new = malloc(sizeof(t_node)); // alocamo o novo nó
			if (new == NULL) // se tivermos algum erro de alocação saímos do programa
				exit (ERROR_MALLOC);
			new->c = i; // c recebe o valor de i (mesmo que o ASCII)
			new->freq = enc.freq_tab[i]; // a frequência do caracter é salvo no nó também
			new->r = NULL; // os ponteiros são zerados 
			new->l = NULL; // os ponteiros são zerados 
			new->next = NULL; // os ponteiros são zerados 
			insert_sort(new); // inserimos esse nó de maneira ordenada na lista
		}
	}
}
