/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:43:37 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/18 13:05:55 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It returns the size of the encoded string.
 * 
 * @return The size of the string that will be coded.
 */
static int	get_size_strcoded() // descobre o tamanho que terá o texto codificado 
{
	int size; // recebe o tamanho total do texto

	size = 0; // inicializa em zero
	for (int i = 0; enc.text[i]; i++) // enquanto não percorremos o texto todo 
		size += strlen(enc.dictionary[(int)enc.text[i]]); // somamos em size o valor da string corresponente a cada letra
	return (size); // retorna o tamanho descoberto
}

/**
 * It gets the size of the coded string, allocates memory for it, and then encodes the text
 */
void	prepare_encode() // codifica o texto, trocando cada caractere pela string de 0s e 1s correspondente
{
	printf("Encoding text...\n"); // Avisamos que estamos nessa fase
	int		size_coded; // int auxiliar para armazenar o tamanho que terá o texto codificado

	size_coded = get_size_strcoded(); // size_coded recebe o tamanho que terá o texto codificado
	enc.coded = calloc((size_coded + 1), sizeof(char)); // o tamanho é usado para alocar o dicionário
	for (int i=0; enc.text[i] != '\0'; i++) //
		strcat(enc.coded, enc.dictionary[(int)enc.text[i]]); // percorremos o texto colocando no lugar de cada caracter, sua string de 0 e 1s correspondente
} // ao fim dessa função o texto já está codificado;
