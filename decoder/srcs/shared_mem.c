/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:18:20 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/18 19:06:24 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

/**
 * It takes a file name and a size of a structure and returns a shared memory id
 * 
 * @param file The file that will be used to generate the key.
 * @param size_struct The size of the structure you want to store in the shared memory.
 * 
 * @return The id of the shared memory block
 */
static int get_id_mem_block(char *file, int	size_struct) // cria um ID para a memória compartilhada
{
	key_t key_tree; // key_t é um tipo de inteiro que não varia em número de bits dependendo do sistema operacional 32bits ou 64bits. 
	
	key_tree = ftok(file, 42); //recebe uma chave para o compartilhamento que está ligada a um arquivo, isso garante que a memória compartilhada continue exixtindo mesmo ao fim da execussão de algum dos programas que a utilizam 
	if (key_tree == ERROR_IPC){ // se der erro ao gerar a chave
		printf("ERROR: Failure to find file for shared memory"); // avisamos o problema
		return(ERROR_IPC); // e retornamos o erro
	}
	return (shmget(key_tree, size_struct, 0644 | IPC_CREAT)); // senão a função SHMGET cria ou se conecta a uma memória compartilhada já existente
}

/**
 * This function attaches the shared memory block to the process
 * 
 * @param file The name of the file that will be used to create the shared memory.
 * @param size_struct The size of the structure that will be stored in the shared memory.
 * 
 * @return A pointer to a shared memory block.
 */
t_shm	*attach_mem_block(char *file, int size_struct) // se conecta a memória compartilhada
{
	int	mem_block_id = get_id_mem_block(file, size_struct); // recebe o ID dessa memória compartilhada
	
	if (mem_block_id == ERROR_IPC){ // se der erro ao gerar o ID
		printf("ERROR: Failed creating shared memory"); // avisamos o erro 
		exit (ERROR_IPC); // retornamos
	}
	t_shm	*sh_tree = (t_shm *) shmat(mem_block_id, NULL, 0); //criamos uma struct para receber o ponteiro para essa memória compartilhada retornado pela função SHMAT que se conecta com a mem. comp.
	if (sh_tree == NULL){ // se der erro ao se conectar a esse ponteiro
		printf("ERROR: Failure to attach memory"); // avisamos o erro
		exit (ERROR_SHMAT); // retornamo o erro
	}
	return (sh_tree); // se der tudo certo retornamos um ponteiro pra essa memória compartilhada que tem um ponteiro
}

/**
 * Detach_mem() detaches the shared memory block from the process
 * 
 * @param block The address of the shared memory block.
 * 
 * @return A boolean value.
 */
bool	detach_mem(t_shm *block)
{
	return (shmdt(block) != ERROR_IPC); // se desconecta da memória compartilhada
}

/**
 * It destroys the shared memory block with the given file name
 * 
 * @param file the name of the file that will be used to create the shared memory block.
 * 
 * @return A boolean value.
 */
// bool	destroy_mem(char *file) // não usamos mais essa função aqui, pois quem destruirá será o ENCODER
// {
// 	int	shared_block_id = get_id_mem_block(file, 0);
// 	if (shared_block_id == ERROR_IPC)
// 		return NULL;
// 	return (shmctl(shared_block_id, IPC_RMID, NULL) != ERROR_IPC);
// }

/**
 * It deserializes a tree.
 * 
 * @param arr an array of long integers
 * @param index the index of the array where the next node will be read from
 * 
 * @return The root of the tree.
 */
t_node	*deserialize_tree(long int *arr, int *index) // reconstrói a árvore, levando em conta o array da árvore serializada
/*

																				        1
																				       / \
																				      2   3
																				     / \
																				    4   5
arr = [(1,0), (2,1), (4,2), (5,2), (3,1)]         => deserialização =>         árvore binária  
*/
{
	if (arr[(*index)] == -1){ // se encontrar um -1 é pq chegou a folha
		(*index)++; // avançamos pro próximo
		return NULL; //retornamos
	}
	t_node *root = (t_node *) malloc(sizeof(t_node)); // aloca o espaço para um nó
	root->c = arr[(*index)++]; // o nó recebe o caracter presente no índice
	root->l = deserialize_tree(arr, index); // vai recursivamente andando para a esquerda
	root->r = deserialize_tree(arr, index); // vai recursivamente andando para a direita
	// root->next = deserialize_tree(arr, index); // não precisamos dessa linha por não ser mais uma lista linkada
	return (root); // retornamos a árvore recosntruída
}
