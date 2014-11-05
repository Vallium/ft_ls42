/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 08:24:45 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/05 08:31:17 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const	void *s, int c, size_t n)
{
	const unsigned char	*ptrs;

	while (*ptrs)
	{
		if (*ptrs == (unsigned char)c)
			return ((void *)ptrs);
		ptrs++;
	}
	return (NULL);
}
