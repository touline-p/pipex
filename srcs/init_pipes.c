/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:57:56 by bpoumeau          #+#    #+#             */
/*   Updated: 2022/12/19 00:44:03 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**init_pipes(int ac)
{
	int	**dst;
	int	nb_pipes;
	int	i;

	nb_pipes = ac - 4;
	dst = malloc(sizeof(int *) * nb_pipes);
	if (!dst)
		return (per_ret_null("Error allocating pipes array"));
	i = -1;
	while (i++ < nb_pipes)
	{
		dst[i] = malloc(sizeof(int) * 2);
		if (!dst[i])
			return (free_pipes_arr_n_per(dst, nb_pipes,
					"sub allocating pipes arr"));
		if (pipe(dst[i]))
			return (free_pipes_arr_n_per(dst, nb_pipes, "pipes not working"));
	}
	return (dst);
}
