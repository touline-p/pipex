/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:57:56 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/08 15:38:07 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**init_pipes(int ac)
{
	int	**dst;
	int	nb_pipes;
	int	i;

	nb_pipes = ac - 3;
	if (nb_pipes < 1)
		return (NULL);
	dst = malloc(sizeof(int *) * nb_pipes);
	if (!dst)
		return (per_ret_null("pipes"));
	i = -1;
	while (i++ < nb_pipes - 1)
	{
		dst[i] = malloc(sizeof(int) * 2);
		if (!dst[i])
			return (free_pipes_arr_n_per(dst, nb_pipes,
					"sub allocating pipes arr"));
		if (pipe(dst[i]))
			return (free_pipes_arr_n_per(dst, nb_pipes, "pipes not working"));
	}
	dst[++i] = NULL;
	return (dst);
}
