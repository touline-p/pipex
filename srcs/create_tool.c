/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:58:00 by bpoumeau          #+#    #+#             */
/*   Updated: 2022/12/19 00:44:07 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_ptl	*init_tool(int ac, char **av)
{
	t_ptl	*dst;

	dst = malloc(sizeof(t_ptl *));
	dst->pipes = init_pipes(ac);
	dst->commands = init_commands(ac, av);
	dst->fd_in = open(av[1], O_RDONLY);
	dst->fd_ot = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (dst);
}
