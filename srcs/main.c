/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:58:07 by bpoumeau          #+#    #+#             */
/*   Updated: 2022/12/19 00:44:08 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	t_ptl	*tool;

	tool = init_tool(ac, av);
	if (!tool)
	{
		ft_putendl_fd("Error initializing t_ptl", 2);
		return (1);
	}
	exec_cmd(tool);
	return (0);
}
