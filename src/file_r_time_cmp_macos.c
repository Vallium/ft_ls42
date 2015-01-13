/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_r_time_cmp_macos.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 12:11:09 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/06 12:11:13 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			file_r_mtime_cmp(void *ptr1, void *ptr2)
{
	t_file *f1;
	t_file *f2;

	f1 = (t_file *)ptr1;
	f2 = (t_file *)ptr2;
	if (f1->stats.st_mtimespec.tv_sec == f2->stats.st_mtimespec.tv_sec)
		return (f1->stats.st_mtimespec.tv_nsec - f2->stats.st_mtimespec.tv_nsec
		? f1->stats.st_mtimespec.tv_nsec - f2->stats.st_mtimespec.tv_nsec :
		file_r_name_cmp(ptr1, ptr2));
	return (f1->stats.st_mtimespec.tv_sec - f2->stats.st_mtimespec.tv_sec ?
	f1->stats.st_mtimespec.tv_sec - f2->stats.st_mtimespec.tv_sec :
	file_r_name_cmp(ptr1, ptr2));
}

int			file_r_atime_cmp(void *ptr1, void *ptr2)
{
	t_file *f1;
	t_file *f2;

	f1 = (t_file *)ptr1;
	f2 = (t_file *)ptr2;
	if (f1->stats.st_atimespec.tv_sec == f2->stats.st_atimespec.tv_sec)
		return (f1->stats.st_atimespec.tv_nsec - f2->stats.st_atimespec.tv_nsec
		? f1->stats.st_atimespec.tv_nsec - f2->stats.st_atimespec.tv_nsec :
		file_r_name_cmp(ptr1, ptr2));
	return (f1->stats.st_atimespec.tv_sec - f2->stats.st_atimespec.tv_sec ?
	f1->stats.st_atimespec.tv_sec - f2->stats.st_atimespec.tv_sec :
	file_r_name_cmp(ptr1, ptr2));
}

int			file_r_ctime_cmp(void *ptr1, void *ptr2)
{
	t_file *f1;
	t_file *f2;

	f1 = (t_file *)ptr1;
	f2 = (t_file *)ptr2;
	if (f1->stats.st_ctimespec.tv_sec == f2->stats.st_ctimespec.tv_sec)
		return (f1->stats.st_ctimespec.tv_nsec - f2->stats.st_ctimespec.tv_nsec
		? f1->stats.st_ctimespec.tv_nsec - f2->stats.st_ctimespec.tv_nsec :
		file_r_name_cmp(ptr1, ptr2));
	return (f1->stats.st_ctimespec.tv_sec - f2->stats.st_ctimespec.tv_sec ?
	f1->stats.st_ctimespec.tv_sec - f2->stats.st_ctimespec.tv_sec :
	file_r_name_cmp(ptr1, ptr2));
}
