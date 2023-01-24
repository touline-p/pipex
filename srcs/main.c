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

static void	main_eu(char *msg);

int	main(int ac, char **av, char **env)
{
	t_ptl	*tool;

	if (ac < 5)
	{
		main_eu("args number");
		return (1);
	}
	close(2);
	tool = init_tool(ac, av, env);
	if (!tool)
	{
		main_eu("Error initializing t_ptl");
		return (1);
	}
	exec_cmd(tool, env);
	clean_t_ptl_ret_null(tool);
	exit(0);
}

static void	main_eu(char *msg)
{
	if (write(2, "Error\n", 6) == -1)
		perror("main_eu");
	if (write(2, msg, ft_strlen(msg)) == -1)
		perror("main_eu");
	if (write(2, "\n", 1) == -1)
		perror("main_eu");
}