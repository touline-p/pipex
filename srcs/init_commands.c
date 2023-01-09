/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:17:16 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/09 19:06:20 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*cmd_creator(char *name);
t_cmd	*get_t_cmd(char *str, char **env, char *name);

t_cmd	**init_commands(int ac, char **av, char **env)
{
	t_cmd	**dst;
	int		i;

	dst = malloc(sizeof(t_cmd *) * (ac - 2));
	if (!dst)
		return (per_ret_null("Error allocating commands array"));
	i = 0;
	while (i + 2 < ac - 1)
	{
		dst[i] = get_t_cmd(av[i + 2], env, av[1]);
		if (!dst[i])
			return (free_t_cmds_n_per(dst, i, "Error sub allocate t_cmd"));
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

t_cmd	*cmd_creator(char *name)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->absolute_path = NULL;
	new->args = NULL;
	new->file_in = name;
	return (new);
}

char	*ft_strjoin_three(char *a, char *b, char *c)
{
	int		ln;
	char	*dst;
	int		i;

	ln = ft_strlen(a) + ft_strlen(b) + ft_strlen(c) + 1;
	dst = malloc(ln);
	if (!dst)
		return (NULL);
	ln = 0;
	i = 0;
	while (a[i])
		dst[ln++] = a[i++];
	i = 0;
	while (b[i])
		dst[ln++] = b[i++];
	i = 0;
	while (c[i])
		dst[ln++] = c[i++];
	dst[ln++] = c[i++];
	return (dst);
}

char	*get_absolute_path(char *cmd, char **env)
{
	char	**path;
	int		i;
	char	*test;

	path = get_n_split_path(env);
	if (!path)
		return (per_ret_null("Error getting path"));
	i = -1;
	while (path[++i])
	{
		test = ft_strjoin_three(path[i], "/", cmd);
		if (!test)
			return (per_ret_null("Error allocating test"));
		if (!access(test, F_OK))
		{
			ft_free_split(path);
			return (test);
		}
		free(test);
	}
	ft_free_split(path);
	test = ft_strdup(cmd);
	if (!test)
		return (per_ret_null("Error duplicating cmd"));
	return (test);
}

t_cmd	*get_t_cmd(char *str, char **env, char *file_in)
{
	t_cmd	*dst;

	dst = cmd_creator(file_in);
	if (!dst)
		return (per_ret_null("Error allocating t_cmd"));
	dst->args = ft_split(str, ' ');
	if (!dst->args)
		return (free_t_cmd_n_per(dst, "Error spliting args"));
	dst->absolute_path = get_absolute_path(dst->args[0], env);
	if (!dst->absolute_path)
	{
		ft_free_split(dst->args);
		free_t_cmd_n_per(dst, "Error getting absolute path");
	}
	return (dst);
}
