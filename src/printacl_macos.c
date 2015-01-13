/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printacl_macos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 13:39:00 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/13 13:39:05 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_acl_attr(t_file **file, int i, char *arg)
{
	if (listxattr(ft_burger(arg, '/', file[i]->name), NULL, 256, 1) > 0)
		ft_putstr("@ ");
	else if (acl_get_link_np(ft_burger(arg, '/', file[i]->name),
										ACL_TYPE_EXTENDED))
		ft_putstr("+ ");
	else
		ft_putstr("  ");
}
