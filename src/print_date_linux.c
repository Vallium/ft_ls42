/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_date_unix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 12:47:49 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/06 12:48:13 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_date(t_file *file)
{
	if (file->stat.st_mtime > time(0) - 15778463 &&
		file->stat.st_mtime < time(0) + 15778463)
		ft_putstr_sub(ctime(&file->stat.st_mtime), 4, 12);
	else
		ft_putstr_sub(ctime(&file->stat.st_mtime), 4, 7),
		ft_putchar(' '),
		ft_putstr_sub(ctime(&file->stat.st_mtime), 20, 4);
}
