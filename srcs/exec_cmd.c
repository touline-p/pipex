/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:18:37 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/09 21:16:42 by bpoumeau         ###   ########lyon.fr   */
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
		close(pp_in[0]);
		close(pp_ot[1]);
		execve(cmd->absolute_path, cmd->args, env);
		perror(cmd->absolute_path);
		exit(errno);
	}
	return (pid);
}

pid_t	first_exec(int fd_in, int *pp_ot, t_cmd *cmd, char **env)
{
	pid_t	pid;

	if (fd_in == -1)
	{
		perror(cmd->file_in);
		return (-2);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(pp_ot[0]);
		dup2(pp_ot[1], STDOUT_FILENO);
		close(fd_in);
		close(pp_ot[1]);
		execve(cmd->absolute_path, cmd->args, env);
		perror(cmd->absolute_path);
		exit(errno);
	}
	return (pid);
}

pid_t	last_exec(int *pp_in, int fd_ot, t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	close(pp_in[1]);
	if (pid == 0)
	{
		dup2(pp_in[0], STDIN_FILENO);
		dup2(fd_ot, STDOUT_FILENO);
		close(pp_in[0]);
		close(fd_ot);
		execve(cmd->absolute_path, cmd->args, env);
		perror(cmd->absolute_path);
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
