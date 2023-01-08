/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:58:52 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/05 18:46:02 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*free_pipes_arr_n_per(int **trash, int signal, char *msg)
{
	perror(msg);
	while (signal--)
		free(trash[signal]);
	free(trash);
	return (NULL);
}

void	*per_ret_null(char *str)
{
	perror(str);
	return (NULL);
}

void	*free_t_cmd(t_cmd *cmd)
{
	ft_free_split(cmd->args);
	free(cmd->absolute_path);
	free(cmd);
	return (NULL);
}

void	*free_t_cmd_n_per(t_cmd *cmd, char *msg)
{
	free_t_cmd(cmd);
	perror(msg);
	return (NULL);
}

void	*free_t_cmds_n_per(t_cmd **cmds, int nb_elem, char *msg)
{
	while (nb_elem--)
		free_t_cmd(cmds[nb_elem]);
	free(cmds);
	perror(msg);
	return (NULL);
}

