/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:26:30 by bpoumeau          #+#    #+#             */
/*   Updated: 2022/12/19 15:25:41 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_n_split_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp("PATH", env[i], 4))
			return (ft_split((env[i]) + 5, ':'));
	return (NULL);
}

