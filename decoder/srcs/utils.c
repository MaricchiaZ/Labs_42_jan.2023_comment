/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:04:53 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 01:36:13 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

/**
 * It returns the current time in milliseconds
 * 
 * @return The time in milliseconds.
 */
long int	get_time(void)
{
	struct timeval    time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * It frees the memory allocated for the tree.
 * 
 * @param root the root of the tree
 * 
 * @return The root of the tree.
 */
void	freeTree(t_node* root) 
{
	if (root == NULL) return;
	freeTree(root->l);
	freeTree(root->r);
	freeTree(root->next);
	free(root);
}
