/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:51:38 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 09:49:22 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It returns the length of a string.
 * 
 * @param s The string to be printed.
 * 
 * @return The length of the string.
 */
int	ft_strlen(unsigned char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * It takes two strings, concatenates them, and returns the result
 * 
 * @param s1 The first string to be joined.
 * @param s2 The string to be appended to the end of s1.
 * 
 * @return A pointer to a string.
 */
unsigned char	*ft_strjoin(unsigned char *s1, unsigned char *s2)
{
	char	*dest;
	int		len;
	int		i;

	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *) malloc (sizeof (char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (s1 && s1[i] != '\0')
		dest[len++] = s1[i++];
	i = 0;
	while (s2 && s2[i] != '\0')
		dest[len++] = s2[i++];
	dest[len] = '\0';
	free(s1);
	return ((unsigned char*)dest);
}

/**
 * It takes a string, a number, a copy of the number, and an index, and returns a string with the
 * number in it
 * 
 * @param str the string that will be returned
 * @param ten the power of 10 that we're currently on.
 * @param cpy_n a copy of the number to be converted to a string
 * @param i the index of the string
 * 
 * @return a pointer to the string.
 */
static void	*str_complete(char *str, int ten, long int cpy_n, int i)
{
	while (ten >= 1)
	{
	str[i] = '0' + (cpy_n / ten);
	cpy_n = cpy_n - (cpy_n / ten) * ten;
	ten = ten / 10;
	i++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * The function ft_itoa() converts an integer to a string
 * 
 * @param n the number to be converted to a string
 * 
 * @return A string with the number in it.
 */
char	*ft_itoa(int n)
{
	int			signal_loc;
	int			ten;
	char		*str;
	int			i;
	long int	cpy_n;

	signal_loc = 0;
	ten = 1;
	i = 1;
	cpy_n = n;
	if (cpy_n < 0)
	{
		signal_loc = 1;
		cpy_n = cpy_n * -1;
	}
	while (ten <= cpy_n / 10)
	{
		ten = ten * 10;
		i++;
	}
	str = (char *) malloc(sizeof(char) * (i + signal_loc + 1));
	if (signal_loc == 1)
		str[0] = '-';
	str_complete(str, ten, cpy_n, signal_loc);
	return (str);
}

/**
 * It frees a matrix
 * 
 * @param mtx The matrix to be freed.
 * 
 * @return A pointer to a pointer to a char.
 */
void	free_matrix(char **mtx)
{
	int	i;

	i = 0;
	if (mtx == NULL)
		return ;
	while (mtx[i])
	{
		free(mtx[i]);
		i++;
	}
	free(mtx);
}

/**
 * It initializes the structure
 */
void	init_struct()
{
	bzero(&enc, sizeof(t_enc));
}

/**
 * It frees the memory allocated for a binary tree.
 * 
 * @param root The root of the tree to be freed.
 * 
 * @return The root of the tree.
 */
static void	freeTree(t_node* root) {
	if (root == NULL) return;
	freeTree(root->l);
	freeTree(root->r);
	free(root);
}

/**
 * It frees all the memory allocated in the program
 */
void	free_struct()
{
	if (enc.text)
		free (enc.text);
	if (enc.freq_tab)
		free (enc.freq_tab);
	if (enc.list)
		free(enc.list);
	if (enc.tree)
		freeTree(enc.tree);
	if (enc.coded)
		free(enc.coded);
}
