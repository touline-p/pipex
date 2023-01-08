/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:18:37 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/08 15:42:49 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	child_exec(int *pp_in, int *pp_ot, t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	close(pp_in[1]);
	if (pid == 0)
	{
		dup2(pp_in[0], STDIN_FILENO);
		close(pp_ot[0]);
		dup2(pp_ot[1], STDOUT_FILENO);
		execve(cmd->absolute_path, cmd->args, env);
		exit(errno);
	}
	return (pid);
}

pid_t	first_exec(int fd_in, int *pp_ot, t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(pp_ot[0]);
		dup2(pp_ot[1], STDOUT_FILENO);
		execve(cmd->absolute_path, cmd->args, env);
		exit(errno);
	}
	return (pid);
}
pid_t	last_exec(int *pp_in, int fd_ot, t_cmd *cmd, char **env)
{
	pid_t pid;

	pid = fork();
	close(pp_in[1]);
	if (pid == 0)
	{
		dup2(pp_in[0], STDIN_FILENO);
		dup2(fd_ot, STDOUT_FILENO);
		execve(cmd->absolute_path, cmd->args, env);
		exit(errno);
	}
	return (pid);
}

void	exec_cmd(t_ptl *tool, char **env)
{
	int	i;
	
	i = 0;
	tool->pid_tab[i] = first_exec(tool->fd_in, tool->pipes[i], 
			tool->commands[i], env);
	check_pid(tool->pid_tab[i++], tool);
	while (tool->commands[i + 1])	
	{
		tool->pid_tab[i] = child_exec(tool->pipes[i - 1],
				tool->pipes[i],
				tool->commands[i], env);
		check_pid(tool->pid_tab[i++], tool);
	}
	tool->pid_tab[i] = last_exec(tool->pipes[i - 1], tool->fd_ot,
			tool->commands[i], env);
	check_pid(tool->pid_tab[i + 1], tool);
	tool->pid_tab[i + 1] = 0;
	wait_tab_pid(tool->pid_tab);
}

void	exec_unic_cmd(t_ptl *tool, char **env)
{
	tool->pid_tab[0] = fork();
	if (tool->pid_tab[0] == 0)
	{
		dup2(tool->fd_in, STDIN_FILENO);
		dup2(tool->fd_ot, STDOUT_FILENO);
		execve(tool->commands[0]->absolute_path, tool->commands[0]->args,
				env);
		exit(errno);
	}
	check_pid(tool->pid_tab[0], tool);
	waitpid(tool->pid_tab[0], NULL, 0);
}
