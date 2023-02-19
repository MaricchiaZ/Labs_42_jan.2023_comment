/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 08:31:19 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/18 15:16:51 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

t_enc	enc;

int	main(int argc, char **argv)
{
	setlocale(LC_ALL, "C.UTF-8"); //define a noção da biblioteca C de estilo de formatação de linguagem natural para um outro especificado. C.UTF-8 - define o local como padrão 'C' e a codificação UTC-8 exibe corretamente todos os caracteres Unicode (110.000 caracteres) usando apenas uma sequencia de bits
	if (!read_args(argc, argv)) // se a leituras dos argumentos não for ok
		return (-1); // retorna erro, e sai do programa
	enc.text_size = ft_strlen(enc.text); // salvamos o tamanho total do texto pronto para ser trabalhado
	printf("\n\tStarting Huffman algorithm\n"); // Avisamos que está se iniciando o algoritmo de Huffman (AH)
	init_list(); //inicializa-se a lista necessária para o AH
	prepare_freq_table(); // prepara a tabela de frequência necessária para o AH
	prepare_list(); // faz-se uma lista encadeada ordenada com os caracteres presentes na tabela
	prepare_huffman_tree(); // monta-se então a Árvore de Huffman (uma árvore binária)
	prepare_dictionary(); // Monta um dicionário usando a Árvore de Huffman
	prepare_encode(); // vai trocar os caracteres do texto pela string correspondente no dicionário
	compress(); // comprime o texto
	printf(ANSI_GREEN "\n\tCompressed text ready in the shared memory\n\n" RESET_COLOR); // avisamos que o texto comprimido vai pra memória compartilhada
	prepare_shared_memory(); // preparamos a memória compartilhada
	free_struct();
	return (0);
}
