/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:18:20 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/18 18:27:38 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It takes a file name and a size of a structure and returns a shared memory id
 * 
 * @param file The file that will be used to generate the key.
 * @param size_struct The size of the structure you want to store in the shared memory.
 * 
 * @return The id of the shared memory block
 */
static int get_id_mem_block(char *file, int	size_struct) // função que uma chave e um id a partir dessa chave 
{
	key_t key_tree; // key_t é um tipo de inteiro específico que não varia em número de bits entre diferentes tipos de sistemas operacionais. 
	key_tree = ftok(file, 42);     // A função ftok (File TO Key) é uma função presente em sistemas operacionais Unix e Linux que gera uma chave de sincronização a partir de um arquivo. Ela é utilizada para associar um arquivo a uma chave de sincronização, permitindo que vários processos possam acessar e sincronizar o acesso a esse arquivo. A chave gerada é única e depende do caminho do arquivo, do ID do projeto e do valor de um caractere de projeto passado como parâmetro. A função ftok é utilizada com outras funções de sincronização, como semaphores e shared memory. //O ID do projeto (project ID) é um valor numérico utilizado pela função ftok para diferenciar diferentes projetos ou aplicações que estão usando a mesma chave de sincronização.

	//recebe uma chave para o compartilhamento que está ligada a um arquivo, isso garante que a memória compartilhada continue exixtindo mesmo ao fim da execussão de algum dos programas que a utilizam 
	if (key_tree == ERROR_IPC){ // se der um erro na criação da chave
		printf("ERROR: Failure to find file for shared memory\n"); // avisamos se não for possívem criar a chave
		return(ERROR_IPC); // retornamos erro
	}
	return (shmget(key_tree, size_struct, 0644 | IPC_CREAT)); // a partir da chave retornamos um int gerado pela função SHMGET que cria ou acessa uma área de memória compartilhada: 1- key: é a chave de sincronização gerada pela função ftok, que é utilizada para identificar a área de memória compartilhada. 2- size: é o tamanho, em bytes, da área de memória a ser criada ou acessada. 3- shmflg: é um conjunto de flags que especificam as permissões de acesso e as opções de criação da área de memória.
}

/**
 * This function attaches the shared memory block to the process
 * 
 * @param file The name of the file that will be used to create the shared memory.
 * @param size_struct The size of the structure that will be stored in the shared memory.
 * 
 * @return A pointer to a shared memory block.
 */
t_shm	*attach_mem_block(char *file, int size_struct) // função que conecta esse programa no bloco de memória criado
{
	int	mem_block_id = get_id_mem_block(file, size_struct); // criamos um int que recebe o ID para a memória compartilhada
	if (mem_block_id == ERROR_IPC){ // se der erro na criação ou acesso dessa memória
		printf("ERROR: Failed creating shared memory\n"); // avisamos a falha
		exit (ERROR_IPC); // saímos do programa
	}
	t_shm	*sh_tree = (t_shm *) shmat(mem_block_id, NULL, 0); // usamos esse id para conectar esse programa à essa memória compartilhada por meio da função SHMAT  que SE CONECTA NA MEM_COMPARTILHADA anexa o segmento de memória compartilhada associado ao identificador de memória compartilhada especificado por shmid para o espaço de endereço do processo de chamada. 1-id da memória compartilhada criada pela shmget    2- usando o NULL o segmento será anexado no primeiro endereço disponível conforme selecionado pelo sistema. 
	
	if (sh_tree == NULL){ // de ser erro ao se conectar nessa memória 
		printf("ERROR: Failure to attach memory\n"); // avisamos o erro
		exit (ERROR_SHMAT); // saímos do programa
	}
	return (sh_tree); // retornamos o ponteiro pra struct que está nesta zona de memória
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
	return (shmdt(block) != ERROR_IPC); //A função shmdt() desacopla (detaches) o segmento de memória compartilhada especificado pelo endereço shmaddr do espaço de endereçamento processo que a chama. Obviamente, o segmento desacoplado deve ser um dentre os segmentos previamente acoplados pelo processo usando shmat. Este segmento não poderá mais utilizado pelo processo após a chamada da função. Valor de retorno: 0 em caso de sucesso e -1 em caso de erro.
}

/**
 * It destroys the shared memory block.
 * 
 * @param file the name of the file to be used as the key for the shared memory block.
 * 
 * @return The return value is a pointer to the shared memory block.
 */
bool	destroy_mem(char *file) 
{
	int	shared_block_id = get_id_mem_block(file, 0); // recupera o id da memória criada
	if (shared_block_id == ERROR_IPC) // se ocorrer algum erro ao pegar o id
		return NULL; // retorna NULL
	return (shmctl(shared_block_id, IPC_RMID, NULL) != ERROR_IPC); ; // SHMCTL executa a operação de controle especificada por cmd no Segmento de memória compartilhada System V cujo identificador é dado em IPC_RMID que marca o segmento a ser destruído, com a flag IPC_RMID o NULL é ignorado
}

/**
 * It takes a tree and turns it into an array
 * 
 * @param root the root of the tree
 * @param arr the array that will be used to store the serialized tree
 * @param index the index of the array where the next element will be inserted
 * 
 * @return The array of long ints.
 */
void	serialize_tree(t_node *root, long int *arr, int *index) // função que transforma a árvore binária em um array
// Serializar a árvore binária é importante para garantir que ela possa ser compartilhada corretamente e de forma segura. Sem a serialização, os nós e ponteiros da árvore poderiam ficar corrompidos ou perdidos, impedindo que a árvore fosse usada corretamente.
/*
		1
	   / \
	  2   3
	 / \
	4   5
   / \
-1    -1
árvore binária          -> serialização ->      arr = [(1,0), (2,1), (4,2), (5,2), (3,1)]
*/
{
	if (root == NULL){ // se chegou a um nó folha seus ponteiros serão null
		arr[(*index)++] = -1; // salva -1 em seu valor
		return ;
	}
	arr[(*index)++] = root->c; // recebe o caracter do nó
	serialize_tree(root->l, arr, index); // chama recursivamente pra direita
	serialize_tree(root->r, arr, index); // chama recursivamente pra esquerda
	//serialize_tree(root->next, arr, index); // essa linha não é necessária porque essa variável 
}

/**
 * It creates a shared memory block, serializes the tree, writes the compressed text and the size of
 * the compressed text, and then waits for the decoder to read the data and write the time it took to
 * decode the text
 */
void prepare_shared_memory() // prepara a memória que será compartilhada com o programa Decoder
{
	t_shm	*block = attach_mem_block("README.md", sizeof(t_shm)); //criamos um ponteiro para a struct shm que apontará para essa memória compartilhada
	int i = 0; // serve para medir a altura/ distância da raiz para os nós na serialização da árvore

	bzero(block, sizeof(t_shm)); // passamos a bzero pra evitar lixo de memória
	serialize_tree(enc.list->start, block->tree_serialize, &i); // colocamos na variável block->tree_serialize da memória compartilhada a árvore binária serializada (em série), o i serve para medir a altura/ distância da raiz para os nós 
	block->time_to_decode = -1; // o tempo decorrido nunca será negativo, então inicializamos ele com -1 para servir de sinalizador de que o programa 2 já foi executado
	block->text_size = enc.text_size; //salvamos na memória compartilhada o tamanho total do texto original
	block->bytes_compress_text = enc.size_compress_text; //salvamos na memória compartilhada o tamanho do texto comprimido
	block->tree_size = enc.col; // salvamos na memória altura da árvore 
	for(int j=0; j < enc.size_compress_text; j++ ) // como o texto compactado é formado por caracteres "estranhos" podendo ter um NULL em algum lugar antes do fim do texto, por isso precisamos passar o texto compactado para a memória compartilhada levando em conta o número de caracteres dele `j < enc.size_compress_text`
		block->compressed_text[j] = enc.compressed_text[j]; // copia-se o texto compactado para a mem. compartilhada
	printf("Waiting for decoder action to count time.... (rund ./decoder)\n"); // avisamos que ESTE programa vai ficar aberto e em espera, até que se execute o programa DECODER
	while (block->time_to_decode == -1); // espera as operações do programa decoder ocorrerem para continuar..... (o programa decoder, ao fim de sua execussão, modifica o valor da variável block->time_to_decode , fazendo com que esse programa saia desse while)
	print_infos(block); // printa as informações no terminal
	detach_mem(block); // se desconecta da memória compartilhada
	destroy_mem("README.md"); // libera a memória compartilhada 
}
