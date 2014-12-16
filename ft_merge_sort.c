/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 17:18:41 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/16 17:18:47 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void			ft_merge(int *tab, int bgg1, int end1, int end2)
{
	int			*tab1;
	int			bgg2;
	int			cnt1;
	int			cnt2;
	int			i;

	bgg2 = end1 + 1;
	cnt1 = bgg1;
	cnt2 = bgg2;
	tab1 = (int*)malloc(sizeof(int) * (end1 - bgg1 + 1));
	i = bgg1 - 1;
	while (i++ <= end1)//cpy du debut du tab
		tab1[i - bgg1] = tab[i];
	i = bgg1 - 1;
	while (i++ <= end2)//merge 2 tabs
	{
		if (cnt1 == bgg2)//all elems premier tab utilises
			break ;//all elems sorted
		else if (cnt2 == (end2 + 1))//all elems second tab utilises
		{
			tab[i] = tab1[cnt1 - bgg1];//add elems du premier sous tab
			cnt1++;
		}
		else if (tab1[cnt1 - bgg1] < tab[cnt2])
		{
			tab[i] = tab1[cnt1 - bgg1];//add un elem du premier sous tab
			cnt1++;//avance ds le 1er ss tab
		}
		else
		{
			tab[i] = tab[cnt2];//add un elem du second tab a la suite
			cnt2++;//avance ds le 2nd ss tab
		}
	}
	free(tab1);
}

void			ft_merge_sort_rec(int *tab, int bgg, int end)
{
	int			mid;

	if (bgg != end)
	{
		mid = (bgg + end) / 2;
		ft_merge_sort_rec(tab, bgg, mid);//sort part 1
		ft_merge_sort_rec(tab, mid + 1, end);//sort part 2
		ft_merge(tab, bgg, mid, end);//merge 2 parts
	}
}

void			ft_merge_sort(int *tab, int lgt)
{
	if (lgt <= 0)
		return ;
	else
		ft_merge_sort_rec(tab, 0, lgt - 1);
}

int				main()
{
	int			tab[20] = {85, 89, 7 , 68, 1, 12, 96, 50, 45, 35, 15, 68, 5, 8, 36, 87, 0, 9, 51, 31};
	int			i;

	i = 0;
	printf("Unsort: ");
	while (i < 20)
	{
		printf("%d, ", tab[i]);
		i++;
	}
	i = 0;
	ft_merge_sort(tab, 20);
	printf("\nSort: ");
	while (i < 20)
	{
		printf("%d, ", tab[i]);
		i++;
	}
	return (0);
}