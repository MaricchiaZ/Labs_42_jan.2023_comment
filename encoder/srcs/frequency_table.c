/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frequency_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 08:31:11 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/17 16:18:46 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It creates a frequency table for the characters in the text. Creating the table with the size of ASCII thus optimizes program execution, because we have a direct access table, by the ASCII value of the character.
 * 
 */
void	prepare_freq_table() // prepara a tabela de frequência de caracteres presentes no texto 
{
	unsigned int	aux;
	
	printf("Making the frequency table...\n"); // sinaliza que começou a montar a tabela de frequência
	enc.freq_tab = (unsigned int *) calloc(256, sizeof(int)); // usamos o tamanho como 256, por conta dos 256 elementos presentes na ASCII, assim, acessa-se a posição correspondente a cada letra usando seu valor em ASCII
	for(int i=0; enc.text[i] != '\0'; i++){ //enquanto não lermos o texto todo
		aux = enc.text[i]; // aux recebe o conteúdo daquele caracter do texto
		enc.freq_tab[aux]++; // sua frequencia é contabilizada no array enc.freq_tab
	}
}
