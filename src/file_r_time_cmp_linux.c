/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_r_time_cmp_linux.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 12:11:09 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/06 12:11:13 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			file_r_time_cmp(void *ptr1, void *ptr2)
{
	t_file *f1;
	t_file *f2;

	f1 = (t_file *)ptr1;
	f2 = (t_file *)ptr2;
	return (f1->stats.st_mtime - f2->stats.st_mtime ?
	f1->stats.st_mtime - f2->stats.st_mtime :
	file_name_cmp(ptr1, ptr2));
}
