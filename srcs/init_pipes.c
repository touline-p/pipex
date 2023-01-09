/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:57:56 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/09 18:23:23 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**init_pipes(int ac)
{
	int	**dst;
	int	nb_pipes;
	int	i;

	nb_pipes = ac - 3;
	dst = malloc(sizeof(int *) * nb_pipes);
	if (!dst)
		return (per_ret_null("pipes"));
	i = 0;
	while (i < nb_pipes - 1)
	{
		dst[i] = malloc(sizeof(int) * 2);
		if (!dst[i])
			return (free_pipes_arr_n_per(dst, nb_pipes,
					"sub allocating pipes arr"));
		if (pipe(dst[i]))
			return (free_pipes_arr_n_per(dst, nb_pipes, "pipes not working"));
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

void	*free_pipes_arr_n_per(int **trash, int signal, char *msg)
{
	perror(msg);
	while (signal--)
		free(trash[signal]);
	free(trash);
	return (NULL);
}
