/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:27:58 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 11:00:26 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECODER_H
#define DECODER_H

//Librarie used in the program.
# include <stdio.h>
# include <locale.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/ipc.h>
# include <sys/shm.h>

//Definition the error codes used in the program.
# define ERROR_IPC -1
# define ERROR_SHMAT 1
# define ERROR_SHMEM 3
# define ERROR_TEXT_NULL 7
# define ERROR_OPEN_COMPRESS_FILE 9

//Definition colors codes used in the program.
# define ANSI_GREEN		"\x1b[32m"
# define RESET_COLOR	"\x1b[0m"

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

//Node struct definition
typedef struct s_node
{
	unsigned char	c;
	int				freq;
	struct s_node	*l, *r, *next;
}	t_node;

// utils.c
long int	get_time(void);
void		freeTree(t_node* root);

// shared.mem.c
t_shm		*attach_mem_block(char *file, int size_struct);
bool		detach_mem(t_shm *block);
t_node		*deserialize_tree(long int *arr, int *index);

// uncompress.c
int	uncompress(t_node *tree, int size_text, unsigned char* text_compress, unsigned char* text_uncompress);

#endif