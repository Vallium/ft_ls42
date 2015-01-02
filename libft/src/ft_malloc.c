/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 15:38:56 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/02 15:39:00 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t n)
{
	void	*ret;

	if (!(ret = malloc(n)))
	{
		ft_putstr_fd("Malloc error: Program quited.", 2);
		exit (EXIT_FAILURE);
	}
	return (ret);
}
