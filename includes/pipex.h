/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:39:48 by bpoumeau          #+#    #+#             */
/*   Updated: 2022/12/19 00:44:09 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_command
{
	char	*absolute_path;
	char	**args;
}	t_cmd;

typedef struct s_pipex_tool
{
	int		**pipes;
	t_cmd	**commands;
	int		fd_ot;
	int		fd_in;
}	t_ptl;

/**
 * Init
 **/

t_ptl	*init_tool(int ac, char **av);
int		**init_pipes(int ac);
t_cmd	**init_commands(int ac, char **av);

/**
 * Exec
 **/

void	exec_cmd(t_ptl *tool);

/**
 * Per
 **/

void	*per_ret_null(char *str);
void	*free_pipes_arr_n_per(int **trash, int signal, char *msg);
void	*free_t_cmd_n_per(t_cmd *cmd, char *msg);

#endif
