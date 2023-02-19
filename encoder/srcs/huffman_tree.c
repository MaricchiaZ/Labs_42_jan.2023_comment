/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:56:53 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/17 18:45:34 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It takes the two nodes with the lowest frequency, combines them into a new node, and inserts the new
 * node into the list
 */
void	prepare_huffman_tree()
{
	printf("Making Huffman tree...\n"); // avisa que está iniciando a etapa de fazer a árvore de Huffman
	t_node	*first, *second, *new; // criamos 3 novos nós
	
	while (enc.list->size > 1){ // enquanto não acabarmos de olhar a lista
		first = remove_init_node(); // o primeiro nó é retirado da lista e salvo nesse temporário first (seu ponteiro next recebe NULL, por que agora ele não está mais inserido na lista)
		second = remove_init_node();// o segundonó é retirado da lista e salvo nesse temporário second (seu ponteiro next recebe NULL, por que agora ele não está mais inserido na lista)
		new = malloc(sizeof(t_node)); // mallocamos um novo nó
		if (new == NULL) // se der erro no malloc
			exit (ERROR_MALLOC); // saímos do programa
		new->c = '+'; // colocamos um caractere não significativo (poderia ser qqr caractere)
		new->freq = (first->freq + second->freq); // a frequência desse novo nó é a soma das frequências dos dois primeiros nós retirados
		new->l = first; //salvamos no ponteiro l (left) o conteúdo do primeiro nó retirado
		new->r = second; //salvamos no ponteiro r (rigth) o conteúdo do segundo nó retirado
		new->next = NULL; // não é mais lista, então o next recebe NULL// AGORA TEMOS UMA ÁRVORE
		insert_sort(new); // colocamos esse novo nó, na lista de frequência ordenada
		enc.tree = enc.list->start; // salvamos o ponteiro pra lista na variável árvore 
	}
}
