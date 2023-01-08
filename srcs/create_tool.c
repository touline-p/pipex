/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:58:00 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/08 17:55:06 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_ptl	*init_tool(int ac, char **av, char **env)
{
	t_ptl	*dst;

	if (ac < 4)
		return (NULL);
	dst = malloc(sizeof(t_ptl *));
	if (!dst)
		return (per_ret_null("can't allocate t_ptl"));
	dst->pid_tab = malloc(sizeof(int) * (ac - 2));
	dst->pipes = init_pipes(ac);
	dst->commands = init_commands(ac, av, env);
	if (!dst->pid_tab || !dst->pipes || !dst->commands)
		return (clean_t_ptl_ret_null(dst));
	printf("init done\n");
	dst->fd_in = open(av[1], O_RDONLY);
	dst->fd_ot = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (dst);
}
