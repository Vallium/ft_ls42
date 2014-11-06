/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 18:35:32 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/06 19:19:26 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char			*ft_strtrim(char const *s)
{
	size_t		start;
	size_t		end;
	char		*str;
	char		*ret;

	str = (char *)s;
	start = 0;
	end = 0;
	while (space(*str))
	{
		*str++;
		start++;
	}
	end = ft_strlen(s);
	while (space(str[end]))
		end--;
	ret = (char *)malloc(sizeof(char) * (end - start + 1));
	while (start++ <= end)
		*ret++ = *str++;
	*ret = 0;
	return (ret);
}
