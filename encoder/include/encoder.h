/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 08:35:25 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 10:33:59 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODER_H
# define ENCODER_H

//Librarie used in the program.
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <locale.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/ipc.h>
# include <sys/shm.h>

//Definition the error codes used in the program.
# define ERROR_IPC -1
# define ERROR_SHMAT 1
# define ERROR_OPEN_FILE 3
# define ERROR_MALLOC 5
# define ERROR_CREATE_FILE 7

//Definition colors codes used in the program.
# define ANSI_GREEN		"\x1b[32m"
# define RESET_COLOR	"\x1b[0m"

//Node struct definition
typedef struct s_node
{
	unsigned char	c;
	int				freq;
	struct s_node	*l, *r, *next;
}	t_node;

//List struct definition
typedef struct s_list
{
	t_node	*start;
	int		size;
}	t_list;

//Shared_memory struct definition
typedef struct s_shm
{
	unsigned char	compressed_text[1000000];
	unsigned char	uncompressed_text[1000000];
	int				bytes_text_in;
	int				bytes_compress_text;
	int				time_to_decode;
	long int		tree_serialize[1000000];
	int				tree_size;
	int				text_size;
}	t_shm;

//Encoder struct definition
typedef struct s_enc
{
	unsigned char	*text;
	int				text_size;
	unsigned int	*freq_tab;
	t_list			*list;
	t_node			*tree;
	int				col;
	char			**dictionary;
	char			*coded;
	int				coded_size;
	unsigned char	*compressed_text;
	int				size_compress_text;
}	t_enc;

//Declare the struct as global
extern t_enc	enc;

// utils.c
int				ft_strlen(unsigned char *s);
unsigned char	*ft_strjoin(unsigned char *s1, unsigned char *s2);
char			*ft_itoa(int n);
void			free_matrix(char **mtx);
void			init_struct();
void			free_struct();

// args_to_text.c
int				read_args(int argc, char **argv);
int				count_c_txt();
void			read_text(char *argv, unsigned char *text_file);

// frequency_table.c
void			prepare_freq_table();

// list.c
void			init_list();
void			insert_sort(t_node *node);
t_node			*remove_init_node();
void			prepare_list();

// huffman_tree.c
void			prepare_huffman_tree();

// dictionary.c
void			make_dictionary(char **dictionary, t_node *root, char *code_c, int col);
void			prepare_dictionary();

// encode_text.c
void			prepare_encode();

// compress.c
void			compress();

// shared_mem.c
t_shm		*attach_mem_block(char *file, int size_struct);
void		serialize_tree(t_node *root, long int *arr, int *index);
void 		prepare_shared_memory();

// print_text_infos.c
void		print_infos(t_shm *block);

#endif
