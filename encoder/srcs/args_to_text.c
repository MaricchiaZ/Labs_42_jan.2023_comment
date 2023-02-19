/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_to_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:50:51 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/17 16:04:11 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"


/**
 * It reads the arguments passed to the program and stores them in a string. If the argument is a text file, checking if the file exists and if it is readable. Concatena the text file to the string that will hold the text to be encoded.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The array of arguments passed to the program.
 * 
 * @return 1 if the arguments are valid, 0 otherwise.
 */
int	read_args(int argc, char **argv)
{
	int	i_args = 1; // irá percorrer os argvs e já inicia em 1 pra pular o ./a.out
	unsigned char	*text_file = NULL; // string temporária que recebe o texto de dentro do arquivo
	int				size_text; // tamanho do texto de dentro do arquivo

	if(argc < 2){ // se tiver menos de 2 argumentos, não tem texto pra comprimir
		printf("ERROR: Invalid number of arguments.\n"); // avisamos o erro de args
		return(0); // e saímos dessa função com um retorno de 0 = FALSO
	}
	enc.text = (unsigned char *)strdup(""); // enc.text armazena na global o texto final a ser comprimido, aqui iniciamos ela com a strdup("")
	while(argv[i_args]) //enquanto existir argv pra olhar
	{
		text_file = (unsigned char *)strdup(""); // inicializamos a str temporária que recebe o texto de dentro do arquivo
		if (access(argv[i_args], F_OK | R_OK) != -1){ // se esse argumento que estamos olhando (argv[i_args]) for acessável (F_OK), e legivel (R_OK) seu retorno será diferente de -1, então trataremos com o texto dentro deste arquivo
			size_text = count_c_txt(argv[i_args]); // medimos a quantidade de caracteres desse arquivo
			text_file = calloc (size_text + 1, sizeof(unsigned char)); // mallocamos esse tamanho de texto
			read_text(argv[i_args], text_file); // passamos o texto do arquivo para s str temporária text_file
		}
		if (strlen((char*)text_file) > 0) // se o tiver coisa no texto
			enc.text = ft_strjoin(enc.text, text_file); // anexamos ele á string final
		else
			enc.text = ft_strjoin(enc.text, (unsigned char*)argv[i_args]); // caso contrário, usamos o "nome" do arg pra por na string final
		if (i_args < argc - 1) // enquanto não chegarmos no último argumento
			enc.text = ft_strjoin(enc.text, (unsigned char*)" "); // separamos or args passados por um espaço
		free(text_file); // liberamos a memória da string temporária
		i_args++; //vamos para o próximo arg
	}
	return(1); // retornamos 1 quando dá tudo ok
}

/**
 * It counts the number of characters in a text file passed as argument
 * 
 * @param argv the name of the file to be read
 * @return the number of characters in the file.
 */
int	count_c_txt(char *argv) // conta a quantidade de caracteres que tem no texto passado por argumento
{
	FILE *file_txt = fopen(argv, "r"); // abre um texto, somente para leitura, e retorna um ponteiro do tipo FILE
	int	count_char = 0; // conta a quantidade de caracteres do texto

	if (file_txt == NULL) // se o file_txt for NULL
		exit (ERROR_OPEN_FILE); // saímos do programa 
	while (fgetc(file_txt) != -1) //pega os caracteres do arquivo de um em um, e retorna -1 quando não tem caracteres para pegar
		count_char++; // assim conseguimos saber qnts caracteres tem no texto
	fclose(file_txt); // fechamos o file aberto
	return (count_char); // retornamos a contagem
}

/**
 * It reads the text file passed as argument and stores it in an array
 * 
 * @param argv the name of the file to be read
 * @param text_file This is the array that will hold the text file.
 */
void	read_text(char *argv, unsigned char *text_file) // salva o texto do arquivo em uma string
{
	FILE	*text = fopen(argv, "r"); //a abre o aquivo para leitura
	char	c; // char temporário para receber o que se lê do texto
	int		i = 0;
	
	if (text == NULL) // se a função fopen não operar normalmente
		exit (ERROR_OPEN_FILE);  // saímos do programa
	while (!feof(text)){ // test end-of-file indicator - enquanto não chegarmos no fim do arquivo
		c = fgetc(text); // c recebe cada um dos caracteres do arquivo
		if (c != -1){ // se ainda n acabou o arquivo
			text_file[i] = c; // passamos c para a string
			i++; // avançamos para a próxima posição
		}
	}
}
