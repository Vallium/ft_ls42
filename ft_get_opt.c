/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 12:43:29 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/12 12:41:36 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int				ft_get_opt(int argc, char **argv, char *optstr)
{
	static int	nbarg = 1;
	static int	i = 0;
	char		*ret;

	if (!argv[nbarg][i])
	{
		i = 0;
		nbarg++;
		if (nbarg == argc)
			return (-1);
	}
	if (!i)
	{
		if (argv[nbarg][0] == '-' && argv[nbarg][1] != '-'  && argv[nbarg][1])
			i++;
		else
			return (-1);
	}
	ret = ft_strchr(optstr, argv[nbarg][i++]);
	return (!ret ? '?' : *ret);
}
