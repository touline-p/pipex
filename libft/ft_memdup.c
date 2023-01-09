/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:46:51 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/01/09 21:09:14 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void *src, size_t ln)
{
	void	*dst;

	dst = malloc(ln);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, ln);
	return (dst);
}
