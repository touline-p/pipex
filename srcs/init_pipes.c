/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:57:56 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/11 15:53:05 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	*init_pipes(int ac)
{
	int	*dst;
	int	nb_pipes;
	int	i;

	nb_pipes = ac - 3;
	dst = malloc(sizeof(int) * (nb_pipes * 2 + 1));
	if (!dst)
		return (per_ret_null("pipes"));
	i = 0;
	while (i < nb_pipes - 1)
	{
		if (pipe(&dst[i]))
			return (free_pipes_arr_n_per(dst, "pipes not working"));
		i += 2;
	}
	dst[i] = 0;
	return (dst);
}

void	*free_pipes_arr_n_per(int *trash, char *msg)
{
	perror(msg);
	free(trash);
	return (NULL);
}
