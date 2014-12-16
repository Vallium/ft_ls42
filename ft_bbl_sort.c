/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bbl_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 14:37:55 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/16 15:07:13 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void			ft_swap_char(char *c1, char *c2)
{
	char		tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

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

int				main()
{
	char		tab[11] = "dfhgabjice\0";

	printf("Unsort:\n%s.\n", tab);
	ft_bbl_sort(tab);
	printf("Sort:\n%s.\n", tab);
}
