/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 12:33:04 by aalliot           #+#    #+#             */
/*   Updated: 2014/11/17 15:20:16 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = (char*)malloc(ft_strlen(s1) * sizeof(char) + sizeof(char));
	if (!s2)
		return (NULL);
	ft_strcpy(s2, s1);
	return (s2);
}
