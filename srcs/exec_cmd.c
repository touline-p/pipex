/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:18:37 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/10 19:20:36 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	_error_usage(char *str);

pid_t	child_exec(int *pp_in, int *pp_ot, t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pp_in[0], STDIN_FILENO);
		dup2(pp_ot[1], STDOUT_FILENO);
		close(pp_in[0]);
		close_pipes(&pp_ot[1]);
		execve(cmd->absolute_path, cmd->args, env);
		_error_usage(cmd->absolute_path);
	}
	close(pp_in[0]);
	close(pp_ot[1]);
	return (pid);
}

static void	_error_usage(char *str)
{
	if (*str)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else
		ft_putendl_fd(": permission denied", 2);
	exit(errno);
}

pid_t	first_exec(int fd_in, int *pp_ot, t_cmd *cmd, char **env)
{
	pid_t	pid;

	if (fd_in == -1)
		return (-2);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(pp_ot[1], STDOUT_FILENO);
		close(fd_in);
		close_pipes(pp_ot);
		execve(cmd->absolute_path, cmd->args, env);
		_error_usage(cmd->absolute_path);
	}
	close(fd_in);
	close(pp_ot[1]);
	return (pid);
}

pid_t	last_exec(int *pp_in, int fd_ot, t_cmd *cmd, char **env)
{
	pid_t	pid;

	if (fd_ot == -1)
		return (-2);
	close(pp_in[1]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pp_in[0], STDIN_FILENO);
		dup2(fd_ot, STDOUT_FILENO);
		close_pipes(pp_in);
		close(fd_ot);
		execve(cmd->absolute_path, cmd->args, env);
		_error_usage(cmd->absolute_path);
	}
	close(fd_ot);
	close(pp_in[0]);
	return (pid);
}

void	exec_cmd(t_ptl *tool, char **env)
{
	int	i;

	i = 0;
	tool->pid_tab[i] = first_exec(tool->fd_in, &tool->pipes[i * 2],
			tool->commands[i], env);
	check_pid(tool->pid_tab[i++], tool);
	while (tool->commands[i + 1])
	{
		tool->pid_tab[i] = child_exec(&tool->pipes[i * 2 - 2],
				&tool->pipes[i * 2],
				tool->commands[i], env);
		check_pid(tool->pid_tab[i++], tool);
	}
	tool->pid_tab[i] = last_exec(&tool->pipes[i * 2 - 2], tool->fd_ot,
			tool->commands[i], env);
	check_pid(tool->pid_tab[i + 1], tool);
	tool->pid_tab[i + 1] = 0;
	wait_tab_pid(tool->pid_tab);
}
