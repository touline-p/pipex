/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:39:48 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/08 15:01:51 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/errno.h>
# include <sys/wait.h>

typedef struct s_command
{
	char	*absolute_path;
	char	**args;
}	t_cmd;

typedef struct s_pipex_tool
{
	int		**pipes;
	pid_t	*pid_tab;
	t_cmd	**commands;
	int		fd_ot;
	int		fd_in;
}	t_ptl;

/**
 * Init
 **/

t_ptl	*init_tool(int ac, char **av, char **env);
int		**init_pipes(int ac);
t_cmd	**init_commands(int ac, char **av, char **env);

/**
 * Per
 **/

void	*per_ret_null(char *str);
void	*free_pipes_arr_n_per(int **trash, int signal, char *msg);
void	*free_t_cmds_n_per(t_cmd **cmd, int nb_elem, char *msg);
void	*free_t_cmd_n_per(t_cmd *cmd, char *msg);
void	*free_t_cmd(t_cmd *cmd);

/**
 * Parse Path
 **/

char **get_n_split_path(char **env);

/**
 * exec command
 **/

void	exec_cmd(t_ptl *tool, char **env);
pid_t	child_exec(int *pp_in, int *pp_ot, t_cmd *cmd, char **env);
void	exec_unic_cmd(t_ptl *tool, char **env);

/**
 * wait n clean
 **/

void	wait_tab_pid(pid_t *tab);
void	*clean_t_ptl_ret_null(t_ptl *dst);
void	check_pid(pid_t pid, t_ptl *tool);

#endif
