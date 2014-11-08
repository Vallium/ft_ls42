/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 19:27:59 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/08 20:04:04 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	printf("fonction start\n");
	t_list		*new_list;
	t_list		*start;
	t_list		*tmp;

	new_list = NULL;

	if (!lst || !f)
	{
		printf("!lst || !f)\n");
		return (NULL);
	}
	tmp = (*f)(lst);
	printf("%p, %s, %i\n", tmp, (char *)tmp->content, (int)tmp->content_size);
	//new_list = ft_lstnew(tmp->content, tmp->content_size);
	if (!new_list)
	{
		printf("!start\n");
		return (NULL);
	}
	printf("salut");
	start = new_list;
	printf("sqlut");
	printf("lst = %p, %p",lst, lst->next);
	while (lst->next)
	{
		printf("new elem|n");
		tmp = f(lst->next);
		new_list = ft_lstnew(lst->content, lst->content_size);
		if (!new_list)
		{
			return (NULL);
			ft_lstdel(&start, &ft_bzero);
		}
		lst = lst->next;
		new_list = new_list->next;
	}
	return (start);
}
