/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:04:26 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/05 14:22:52 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isprint(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dst, const char *src);
int		ft_isspace(int c);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
int		ft_isspace(int c);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const	void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
char	*ft_strncpy(char *dst, const char *src, size_t n);
char	*ft_strrchr(const char *s, int c);
char		*ft_strstr(const char *str, const char *to_find);
char	*ft_strchr(const char *s, int c);
char	*ft_strcat(char *s1, const char *s2);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
