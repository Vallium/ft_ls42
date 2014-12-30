/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 12:43:29 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/13 12:37:56 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int				ft_get_opt(int argc, char **argv, t_opt *opt)
{
	static int	i = 0;
	char		*ret;

	if (!argv[opt->nbarg][i]) // si de lire l'arg
	{
		i = 0;
		opt->nbarg++;
		if (opt->nbarg == argc) //si plus d'arg
			return (-1);
	}
	if (!i)
	{
		if (argv[opt->nbarg][0] == '-' && argv[opt->nbarg][1] != '-'
			&& argv[opt->nbarg][1]) // si arg valide
			i++;
		else
		{
			if (argv[opt->nbarg][0] == '-' && argv[opt->nbarg][1] == '-')
				opt->nbarg++;
			return (-1);
		}
	}
	ret = ft_strchr(opt->optstr, argv[opt->nbarg][i++]);
	if (!ret)
		opt->err = argv[opt->nbarg][i - 1];
	return (!ret ? '?' : *ret);
}
