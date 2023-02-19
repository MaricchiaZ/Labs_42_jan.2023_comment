/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:47:06 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/18 15:12:49 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It takes the coded text and converts it into a compressed text. Checking if the current bit is 1, If it is, it is shifting the mask to the left by j bits and then ORing it with the byte.
 * 
 */
void	compress() // função que coleta 8 caracteres do texto codificado e passa essa sequência para o binário de um único char. Assim a cada 8 caracteres viram apenas 1, e a compressão ocorre
{
	printf("Compressing the data..."); // avisamos que estamos iniciando essa faze
	unsigned char	mask, byte = 0; // criamos 2 chars auxiliares 
	int	j = 7; // vamos decrementar esse j, assim contamos de 8 em 8
	int	i_ct = 0; //percorrerá a string do texto comprimido e será um contador dos caracteres presentes no texto comprimido

	enc.compressed_text = (unsigned char *)calloc(enc.text_size + 1, sizeof(char)); // malocamos o tamanho do texto original, pois assim é certeza que caberá o texto comprimido
	for (int i = 0; enc.coded[i]; i++){ // enquanto nao acabar de ler o texto
		mask = 1; // máscara recebe 1 que em binário vale 0000 0001
		if (enc.coded[i] == '1'){ // se o valor de enc.coded[i] for um 1
			mask = mask << j; // empurramos esse 1 na máscara até a posiçao indicada por j (ex: j=3 0000 0100)
			byte = byte | mask; // passamos o 1 da máscara para o byte
		}
		j--; // decrementamos o J para saber qnd deu 1 byte (ele será -1 após ter andado 8x)
		if (j < 0){ // one byte completed // aqui j= -1, e temos um byte completo já manipulado
			enc.compressed_text[i_ct] = byte; // passamos ese byte pra a variável que contém o texto comprimido
			i_ct++; // avançamos para o próximo byte do texto comprimido
			byte = 0; //zeramos o valor do char byte
			j = 7; // j volta a valer 7
		} // isso se repete até acabar o texto codificado
	}
	if (j != 7){ // the last byte incompleted // se acabado de ler o texto codificado e o byte não foi passado ainda pro texto (pq ele não era -1)
		enc.compressed_text[i_ct] = byte; // colocamos esse último byte no texto comprimido
		i_ct++; // e acrescentamos uma unidade em i_ct, por que agora ela nos dará a informação de quantos caracteres compõe o texto comprimido
	}
	enc.size_compress_text= i_ct; //salvamos o tamanho do texto comprimido na struct global
}
