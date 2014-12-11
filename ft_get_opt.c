/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 12:43:29 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/11 19:50:01 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_get_opt(int argc, char **argv, char *optstr)
{
	static char		*nxtchr;
	static int		optind; //`optind' communicates from one call to the next how much of ARGV has been scanned so far
	char			buff[BUFF_SIZE + 1];
	int				ret;

	return (ret == 0 ? 0 : 1);
}
/*
	static char		*mem;
	char			buff[BUFF_SIZE + 1];
	int				ret;

	ret = 1;
	if (BUFF_SIZE <= 0 || !optstr)
		return (-1);
	if (!mem)
		mem = ft_strnew(0);
	while (!(ft_strchr(mem, '\n')))
	{
		buff[ret] = 0;
		mem = ft_strjoin(mem, buff);
	}
	if (ft_strchr(mem, '\n') || ((optstr = ft_strdup(mem)) && 0))
		optstr = ft_strsub(mem, 0, ft_strchr(mem, '\n') - mem + 1);
	if (ret)
		optstr[ft_strlen(optstr) - 1] = 0;
	mem = ft_strsub(mem, ft_strchr(mem, '\n') - mem + 1, \
			ft_strlen(ft_strchr(mem, '\n')));
	return (ret == 0 ? 0 : 1);
*/
