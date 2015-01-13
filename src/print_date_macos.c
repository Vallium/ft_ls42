/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_date_macos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 12:47:49 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/06 12:48:13 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_adate(t_file *file)
{
	if (file->stats.st_atimespec.tv_sec > time(0) - (365 / 2  * 86400) &&
		file->stats.st_atimespec.tv_sec < time(0) + (365 / 2  * 86400))
		ft_putstr_sub(ctime(&file->stats.st_atimespec.tv_sec), 4, 12);
	else
		ft_putstr_sub(ctime(&file->stats.st_atimespec.tv_sec), 4, 7),
		ft_putchar(' '),
		ft_putstr_sub(ctime(&file->stats.st_atimespec.tv_sec), 20, 4);
}

void		print_mdate(t_file *file)
{
	if (file->stats.st_mtimespec.tv_sec > time(0) - (365 / 2  * 86400) &&
		file->stats.st_mtimespec.tv_sec < time(0) + (365 / 2  * 86400))
		ft_putstr_sub(ctime(&file->stats.st_mtimespec.tv_sec), 4, 12);
	else
		ft_putstr_sub(ctime(&file->stats.st_mtimespec.tv_sec), 4, 7),
		ft_putchar(' '),
		ft_putstr_sub(ctime(&file->stats.st_mtimespec.tv_sec), 20, 4);
}

void		print_cdate(t_file *file)
{
	if (file->stats.st_ctimespec.tv_sec > time(0) - (365 / 2  * 86400) &&
		file->stats.st_ctimespec.tv_sec < time(0) + (365 / 2  * 86400))
		ft_putstr_sub(ctime(&file->stats.st_ctimespec.tv_sec), 4, 12);
	else
		ft_putstr_sub(ctime(&file->stats.st_ctimespec.tv_sec), 4, 7),
		ft_putchar(' '),
		ft_putstr_sub(ctime(&file->stats.st_ctimespec.tv_sec), 20, 4);
}

void		print_date(t_file *file)
{
	if (g_u)
		print_adate(file);
	else
		print_mdate(file);
}
