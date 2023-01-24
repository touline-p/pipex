/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:18:37 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/11 15:52:05 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		_error_usage(char *str);
static pid_t	_child_exec(int *pp_in, int *pp_ot, t_cmd *cmd, char **env);
static pid_t	_first_exec(int fd_in, int *pp_ot, t_cmd *cmd, char **env);
static pid_t	_last_exec(int *pp_in, int fd_ot, t_cmd *cmd, char **env);

/**
 * exec command is the switchman of pipex program. It centralizes all the
 * executions and is the one launching each forkings.
 *
 * it also stocks all the pid returned by the _exec ft (first, child and last)
 * to wait for them in wait_arr_pid.
 **/

void	exec_cmd(int ac, t_ptl *tool, char **env)
{
	int	i;
	int	signal;

	i = 0;
	signal = _first_exec(tool->fd_in, &tool->pipes[i * 2],
			tool->commands[i], env);
	i++;
	while (tool->commands[i + 1] && signal != -2)
	{
		signal = _child_exec(&tool->pipes[i * 2 - 2],
				&tool->pipes[i * 2],
				tool->commands[i], env);
		i++;
	}
	if (signal != -2)
		_last_exec(&tool->pipes[i * 2 - 2],
			tool->fd_ot,
			tool->commands[i], env);
	if (signal == -2)
		perror("forks");
	wait_this(ac - 3);
}

static pid_t	_first_exec(int fd_in, int *pp_ot, t_cmd *cmd, char **env)
{
	pid_t	pid;

	if (fd_in == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (-2);
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

static pid_t	_last_exec(int *pp_in, int fd_ot, t_cmd *cmd, char **env)
{
	pid_t	pid;

	if (fd_ot == -1)
		return (-2);
	close(pp_in[1]);
	pid = fork();
	if (pid == -1)
		return (0);
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

static pid_t	_child_exec(int *pp_in, int *pp_ot, t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-2);
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
