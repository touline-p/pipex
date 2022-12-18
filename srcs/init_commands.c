/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:17:16 by bpoumeau          #+#    #+#             */
/*   Updated: 2022/12/19 00:44:05 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*cmd_creator(void);
t_cmd	*get_t_cmd(char *str);

t_cmd	**init_commands(int ac, char **av)
{
	t_cmd	**dst;
	int		i;

	dst = malloc(sizeof(t_cmd *) * ac - 3);
	if (!dst)
		return (per_ret_null("Error allocating commands array"));
	i = 0;
	while (i + 2 < ac - 1)
	{
		dst[i] = get_t_cmd(av[i + 2]);
		if (!dst[i])
			return (free_t_cmd_n_per(dst, "Error sub allocate t_cmd"));
		i++;
	}
	return (dst);
}

t_cmd	*cmd_creator(void)
{
	t_cmd	*new;

	new = malloc(t_cmd);
	if (!new)
		return (NULL);
	new->absolute_path = NULL;
	new->args = NULL;
	return (new);
}

char	*get_absolute_path(char *cmd, char **env)
{
	char	**path;
	int		i;
	char	*test;

	path = get_n_split_path(env);
	if (!path)
		return (per_ret_null("Error alloc path arr"));
	i = -1;
	while (path[++i])
	{
		test = ft_strjoin_n(3, path[i], "/", cmd);
		if (!access(test, F_OK))
		{
			free_split(path);
			return (test);
		}
		free(test);
	}
	free_split(path);
	test = ft_strdup(cmd);
	if (!test)
		return (per_ret_null("Error duplicating cmd"));
	return (test);
}

t_cmd	*get_t_cmd(char *str, char **env)
{
	t_cmd	*dst;

	dst = cmd_creator();
	if (!dst)
		return (free_t_cmd_n_per("Error allocating t_cmd"));
	dst->args = ft_split(str, ' ');
	if (!dst->args)
		return (free_t_cmd_n_per("Error spliting args"));
	dst->commands = get_absolute_path(str[0]);
	if (!dst->commands)
		return (free_t_cmd_n_per("Error getting cmd"));
	return (dst);
}
