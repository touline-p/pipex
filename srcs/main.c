/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:58:07 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/11 15:53:09 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_ptl	*tool;

	if (ac < 5)
	{
		ft_putendl_fd("not enough args", 2);
		return (1);
	}
	tool = init_tool(ac, av, env);
	if (!tool)
	{
		ft_putendl_fd("Error initializing t_ptl", 2);
		return (1);
	}
	exec_cmd(tool, env);
	clean_t_ptl_ret_null(tool);
	exit(0);
}
