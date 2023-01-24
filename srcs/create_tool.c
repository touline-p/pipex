/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:58:00 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/11 15:45:44 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Init tool is init a single structure which contains all information 
 * necessary for the execution part.
 *
 * Thing to know
 * I init an array of pipes first. It implies that I need to close all pipes
 * infile and outfile each time I'd fork.
 **/

t_ptl	*init_tool(int ac, char **av, char **env)
{
	t_ptl	*dst;

	dst = malloc(sizeof(t_ptl));
	if (!dst)
		return (per_ret_null("can't allocate t_ptl"));
	dst->fd_in = open(av[1], O_RDONLY);
	if (dst->fd_in == -1)
		perror(av[1]);
	dst->fd_ot = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dst->fd_ot == -1)
		perror(av[ac - 1]);
	dst->pipes = init_pipes(ac);
	dst->commands = init_commands(ac, av, env);
	if (!dst->pipes || !dst->commands)
	{
		perror("init tool");
		return (clean_t_ptl_ret_null(dst));
	}
	return (dst);
}
