/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 12:43:29 by adoussau          #+#    #+#             */
/*   Updated: 2014/12/13 12:37:56 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int				ft_get_opt(int argc, char **argv, t_opt *opt)
{
	static int	i = 0;
	char		*ret;

	if (!argv[opt->nbarg][i])
	{
		if (!i)
			return (0);
		i = 0;
		opt->nbarg++;
		if (opt->nbarg == argc)
			return (-1);
	}
	if (!i)
	{
		if (argv[opt->nbarg][0] == '-' && argv[opt->nbarg][1] != '-'
			&& argv[opt->nbarg][1])
			i++;
		else
		{
			if (argv[opt->nbarg][0] == '-' && argv[opt->nbarg][1] == '-')
			{
				if (argv[opt->nbarg][2])
				{
					opt->err = '-';
					return ('?');
				}
				opt->nbarg++;
			}
			return (-1);
		}
	}
	if (!(ret = ft_strchr(opt->optstr, argv[opt->nbarg][i++])))
		opt->err = argv[opt->nbarg][i - 1];
	return (!ret ? '?' : *ret);
}
