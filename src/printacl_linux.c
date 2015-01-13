/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printacl_linux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 13:39:13 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/13 13:39:17 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_acl_attr(t_file **file, int i, char *arg)
{
	if (listxattr(ft_burger(arg, '/', file[i]->name), NULL, 256) > 0)
		ft_putstr("@ ");
	else
		ft_putstr("  ");
}
