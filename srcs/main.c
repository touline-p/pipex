/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:58:07 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/08 15:03:38 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_tab(char **tab);
void	test(t_ptl *tool);

int	main(int ac, char **av, char **env)
{
	t_ptl	*tool;

	tool = init_tool(ac, av, env);
	if (!tool)
	{
		ft_putendl_fd("Error initializing t_ptl", 2);
		return (1);
	}
	test(tool);
	printf("going to exec\n");
	if (ac == 4)
	{
		printf("it s unic\n");
		exec_unic_cmd(tool, env);
	}
	else
	{
		printf("it s plural\n");
		exec_cmd(tool, env);
	}
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
