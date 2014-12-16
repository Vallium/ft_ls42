/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_q_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 12:17:19 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/16 20:45:20 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void			ft_q_sort(int *tab, int bg, int ed)
{
	const int	pvt = tab[bg];
	int			lft;
	int			rgt;

	lft = bg - 1;
	rgt = ed + 1;
	if (bg >= ed)
		return ;
	while (1)
	{
		while (tab[--rgt] > pvt)
			;
		while (tab[++lft] < pvt)
			;
		if (lft < rgt)
			ft_swap_int(tab, lft, rgt);
		else
			break ;
	}
	ft_q_sort(tab, bg, rgt);
	ft_q_sort(tab, rgt + 1, ed);
}
