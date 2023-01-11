/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:53:37 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/11 14:31:16 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * close pipes is called each time a fork is done. It purpose is to close
 * all the pipes opened during the init.
 **/

void	close_pipes(int *pipes_tab)
{
	int	i;

	i = 0;
	while (pipes_tab[i])
	{
		close(pipes_tab[i]);
		i++;
	}
}
