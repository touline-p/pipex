/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:23:19 by bpoumeau          #+#    #+#             */
/*   Updated: 2022/12/19 00:31:44 by bpoumeau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_issign(int c);
void		ft_bzero(void *dst, size_t n);
void		*ft_memchr(void *buf, int c, size_t length);
int			ft_memcmp(const void *s1, const void *s2, size_t lenght);
void		*ft_memcpy(void *dst, const void *src, size_t lenght);
void		*ft_memmove(void *dst, const void *src, size_t length);
void		*ft_memset(void *dst, int c, size_t length);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *c, int fd);
void		ft_putendl_fd(char *c, int fd);
void		ft_putnbr_fd(int c, int fd);
char		*ft_strchr(const char *s, int c);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strnstr(char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		*ft_calloc(size_t n, size_t size);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_atoi(const char *nptr);
int			ft_atoi_has_overflown(char *str);
char		*ft_itoa(int n);
int			*ft_intarr_set(int *tab, int value, size_t size);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void		*ft_memdup(void *src, size_t ln);
void		ft_swap(int *a, int *b);
int			ft_is_overflowing(char *str);
void		*ft_free_split(char **dst);
#endif
