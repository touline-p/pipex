/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:21:52 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/09 18:42:43 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_tab_pid(pid_t *tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		if (tab[i] > 0)
			waitpid(tab[i], NULL, 0);
		i++;
	}
}

void	clean_int_arr(int **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_t_cmd(t_cmd *command)
{
	int	i;

	free(command->absolute_path);
	if (!command->args)
		return (free(command));
	i = 0;
	while (command->args[i])
		free(command->args[i++]);
	free(command->args);
	free(command);
}

void	free_t_cmds(t_cmd **commands)
{
	int	i;

	if (!commands)
		return ;
	i = 0;
	while (commands[i])
	{
		free_t_cmd(commands[i]);
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
		perror("fork unsucessfull");
		clean_t_ptl_ret_null(tool);
		exit(errno);
	}
}
