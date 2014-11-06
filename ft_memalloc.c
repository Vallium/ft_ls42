/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 13:42:55 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/06 13:49:17 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

void	*ft_memalloc(size_t size)
{
	unsigned char *ptr;

	ptr = (unsigned char *)malloc(size);
	if (ptr)
		while (size--)
			ptr[size - 1] = 0;
	return ((void *)ptr);
}
