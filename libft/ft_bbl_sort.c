/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bbl_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 14:37:55 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/16 16:51:53 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void			ft_bbl_sort(char *tab)
{
	int			bl;
	int			i;

	bl = 0;
	while (!bl)
	{
		bl = 1;
		i = 0;
		while (tab[i + 1])
		{
			if (tab[i] > tab[i + 1])
			{
				ft_swap_char(&tab[i], &tab[i + 1]);
				bl = 0;
			}
			i++;
		}
	}
}
