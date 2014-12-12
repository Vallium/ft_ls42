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

char				ft_get_opt(int argc, char **argv, char *optstr)
{
	static int		i = 0;
	char			*ret;

	if (argv[argc][0] == '-' && argv[argc][1] == '-')
		return (-1);
	while (argv[argc][optind] && argv[argc][0] == '-')
	{
		if ((ret = ft_strchr(optstr, argv[argc][optind])));
		{
			opt.optind++;
			return (*ret);
		}
	}
	return (ret == 0 ? '?' : *ret);
}
