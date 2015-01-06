/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name_cmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 12:08:48 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/06 12:08:53 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			file_name_cmp(void *ptr1, void *ptr2)
{
	t_file *f1;
	t_file *f2;

	f1 = (t_file *)ptr1;
	f2 = (t_file *)ptr2;
	return (ft_strcmp(f1->name, f2->name));
}
