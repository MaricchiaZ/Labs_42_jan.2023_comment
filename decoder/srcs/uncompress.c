/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncompress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:02:40 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/18 18:59:47 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

/**
 * It returns 1 if the bit at position i in byte is 1, and 0 otherwise
 * 
 * @param byte the byte to check
 * @param i the bit we want to check
 * 
 * @return The bit at position i in byte.
 */
static unsigned int	is_bit(unsigned char byte, int i)
{
	unsigned char	mask = (1 << i); // 00000001
	return (byte & mask);
}

/**
 * It takes a Huffman tree and a compressed text, and returns the uncompressed text
 * 
 * @param tree the tree that was created from the header
 * @param size_text the size of the text to be uncompressed
 * @param text_compress the compressed text
 * @param text_uncompress the text that will be uncompressed
 * 
 * @return The number of bytes read from the compressed file.
 */
int	uncompress(t_node *tree, int size_text, unsigned char* text_compress, unsigned char* text_uncompress) // função responsável por descompactar o texto
{
	unsigned char	byte = 0; // usamos um char auxiliar
	int	i, i_tc, i_tuc; // usammos esses ints para:  i-> tamanho do byte, i_tc-> índice que percorre o texto comprimido, i_tuc-> índice que percorre o texto descomprimido
	t_node	*aux = tree; // usamso um nó auxiliar para percorrer a árvore

	i_tc = 0; // percorre o texto comprimido
	i_tuc = 0; // percorre o texto descomprimido
	while (size_text > -1){ // enquanto não acabar o tamanho do texto original
		byte = text_compress[i_tc]; // byte recebe o primeiro caracter do texto comprimido
		for (i = 7; i >= 0; i--){ // i vai de 8 em 8
			aux = is_bit(byte, i) ? aux->r : aux->l ; // é então lido bit a bit do byte, se o bite me questão for for 1, andamos na árvore para a direira, e se for 0, vamos para a esquerda na árvore de Huffman
			if (aux->l == NULL && aux->r == NULL){ // se chegamos a um nó folha...
				if (size_text < 1) // e acabou o texto a ser escrito - ESSA CHECAGEM EVITA QUE O BYTE INCOMPLETO ADICIONE CARACTERES AO FIM DA DESCOMPACTAÇÂO, mantendo o texto idêntico ao original
					return (i_tc); // retornamos a quantidade de caracteres que tinha no texto comprimido
				text_uncompress[i_tuc] = aux->c; // passamos o caracter do nó folha para o texto descomprimido
				i_tuc++; // avançamos para a próxima posição da string do texto descomprimido
				aux = tree; // o nó auxiliar volta a apontar para a raíz da árvore
				size_text--; // decrementamos a qntd de texto a ser escrita ainda.
			}
		}
		i_tc++; // andamos para a próxima posição do texto comprimido
	}
	return (i_tc); // retornamos a qntd total de caracteres no texto comprimido
}
