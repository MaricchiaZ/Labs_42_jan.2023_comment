/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:27:52 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/18 19:07:15 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "decoder.h"

/**
 * The above function is the main function of the decoder. It attaches the shared memory block,
 * deserializes the tree, uncompresses the text and writes the uncompressed text in the shared memory.
 * 
 * @return The number of bytes of the uncompressed text.
 */
int	main()
{
	int			i = 0; // será usado para a deserialização da árvore
	long int	initial_time; // recebe o tempo logo antes de se iniciar a função de decodificar
	long int	final_time; // recebe o tempo logo antes de se iniciar a função de decodificar
	
	setlocale(LC_ALL, "C.UTF-8"); // função que adequa a linguagem c padrão para os caracteres do UNICODE
	t_shm	*block = attach_mem_block("README.md", sizeof(t_shm)); // recebe o ponteiro para a acessar a memória compartilhada
	if (!block){ // se der algum erro ao se conectar a essa memória
		printf("ERROR: Failure reading shared memory\n"); // avisamos que não foi possivel acessar a mem. comp.
		exit (ERROR_SHMEM); // retornamos o erro
	}
	t_node	*tree = deserialize_tree(block->tree_serialize, &i); // a árvore é reconstruída pela deserialização da árvore serializada que está salva mem. comp.
	printf("Decoded....\n"); // avisamos que se iniciará o processo de decodificação
	initial_time = get_time(); // anotamos o horário exato do início da descompactação
	block->bytes_compress_text = uncompress(tree, block->text_size, block->compressed_text, block->uncompressed_text);  // a variável block->uncompressed_text da memória compartilhada recebe o texto descompactado,salvamos a quantidadede caracteres que tinha o texto comprimido em block->bytes_compress_text... (O TEXTO  DESCOMPRIMIDO SERÁ EXIBIDO NO TERMINAL PELA FUNÇÃO ENCODER)
	final_time = get_time(); // anotamos o horário exato do fim da descompactação
	block->text_size = strlen((char *)block->uncompressed_text); // o tamanho do texto descomprimido é salvo na block->text_size da memória compartilhada 
	block->time_to_decode = final_time - initial_time; // salvamos na memória a quantidade de tempo gasto para descompactar
	printf("Sharing operation data with encoder ....\n"); // avisamos que salvamos o resultado das operações aqui na memória compartilhada
	detach_mem(block); // nos desconectamos da memória compartilhada
	printf(ANSI_GREEN "\tUncompressed text ready in the shared memory\n" RESET_COLOR); // avisamos que o texto descomprimido está na memória compartilhada
	printf("(Look at the return in the ./encoder program)\n"); // avisamos para o usuário ver o retorno desse programa é impresso pelo ENCODER
	freeTree(tree); // limpamos a árvore usada
	return (0); // retornamos
}
