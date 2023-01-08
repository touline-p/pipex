/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:21:52 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/08 15:03:40 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_tab_pid(pid_t *tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		waitpid(tab[i], NULL, 0);
		i++;
	}
}

void	clean_int_arr(int **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_t_cmds(t_cmd **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}

void	*clean_t_ptl_ret_null(t_ptl *trash)
{
	clean_int_arr(trash->pipes);
	free(trash->pid_tab);
	free_t_cmds(trash->commands);
	free(trash);
	return (NULL);
}

void	check_pid(pid_t pid, t_ptl *tool)
{
	if (pid == -1)
	{
		clean_t_ptl_ret_null(tool);
		exit(errno);
	}
}
