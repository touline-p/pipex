/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:58:07 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/09 18:43:29 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_tab(char **tab);
void	test(t_ptl *tool);

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
	return (0);
}

void	test(t_ptl *tool)
{
	int	i;

	printf("les couples de pipes \n");
	i = 0;
	while (tool->pipes[i])
	{
		printf("%d, %d\n", tool->pipes[i][0], tool->pipes[i][1]);
		i++;
	}
	printf("les fichiers\n");
	printf("entrees : %d\nsorties : %d\n", tool->fd_in, tool->fd_ot);
	printf("les commandes \n");
	i = 0;
	while (tool->commands[i])
	{
		printf("%s\n", tool->commands[i]->absolute_path);
		print_tab(tool->commands[i]->args);
		i++;
	}
	printf("%p : tool->commands terminating\n", tool->commands[i]);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%d : %s\n", i, tab[i]);
		i++;
	}
}
