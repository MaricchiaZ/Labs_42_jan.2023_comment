/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text_infos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:44:09 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/18 17:26:02 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It prints the decoded text, the original text size, the encoded text size, the decoded text size,
 * the compression percentage, and the time it took to decode the text
 * 
 * @param block pointer to the shared memory block
 */
void	print_infos(t_shm *block) // printa as infos pedidas pelo exercício, a saber, Texto descomprimido, e eficiência do programa
{
	printf("Finish!!!\n\n"); // avisamos que a execussão acabou
	printf("Text decoded:\n"); // avisa que vamos por o texto
	printf("%s\n", block->uncompressed_text); // imprime o texto descodificado enviado pelo decoder
	printf("\n"); // põe uma quebra de linha pra isolar as infos de eficiência
	printf("   _____________________________________________________\n\n"); // delimitador
	printf("\toriginal text size: \t%d bytes\n", enc.text_size); // tamanho do texto original
	printf("\tencoded text size: \t%d bytes\n", block->bytes_compress_text); // tamanho do texto comprimido
	printf("\tdecoded text size \t%d bytes\n", block->text_size); // tamanho do texto descomprimido
	printf("\tcompression to \t\t%.2f %% of original\n", ((float)(block->bytes_compress_text * 100)/enc.text_size)); // taxa de compressão, o quanto o texto comprimido representa do original 
	printf("\ttime to decoder \t%d ms\n", block->time_to_decode); // o tempo que levou para decodificar
	printf("   _____________________________________________________\n\n"); // delimitador
}
