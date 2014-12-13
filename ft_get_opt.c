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

	if (!argv[opt->nbarg][i])
	{
		i = 0;
		opt->nbarg++;
		if (opt->nbarg == argc)
			return (-1);
	}
	if (!i)
	{
		if (argv[opt->nbarg][0] == '-' && argv[opt->nbarg][1] != '-'  && argv[opt->nbarg][1])
			i++;
		else
			return (-1);
	}
	ret = ft_strchr(opt->optstr, argv[opt->nbarg][i++]);
	return (!ret ? '?' : *ret);
}
