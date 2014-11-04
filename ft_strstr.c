/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 19:46:05 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/04 19:49:52 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	scan(char *str, char *to_find)
{
	int		i;

	i = 0;
	while (to_find[i])
	{
		if (str[i] != to_find[i])
			return (0);
		i++;
	}
	return (1);
}

char		*ft_strstr(char *str, char *to_find)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == to_find[0])
			if (scan(&str[i], to_find))
				return (&str[i]);
		i++;
	}
	return (NULL);
}
