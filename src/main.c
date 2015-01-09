/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 11:13:40 by adoussau          #+#    #+#             */
/*   Updated: 2014/12/20 20:52:42 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		usage(void)
{
	ft_putstr_fd("usage: ft_ls [-Ralprt1] [file ...]\n", 2);
}

int			arg_cmp(void *na1, void *na2)
{
	return (ft_strcmp(na1, na2));
}

void		get_opt_assi(int argc, char **argv, t_opt *opt)
{
	char	c;

	opt->optstr = "Ralprt1";
	opt->nb = 1;
	while ((c = ft_get_opt(argc, argv, opt)) > 0)
	{
		if (c == '?')
			ft_putstr_fd("ft_ls: illegal option -- ", 2),
			ft_putchar_fd(opt->err, 2),
			ft_putchar_fd('\n', 2),
			usage(),
			exit (2);
		if (c == 'l')
			g_l = 1;
		else if (c == 'R')
			g_re = 1;
		else if (c == 'a')
			g_a = 1;
		else if (c == 'p')
			g_p = 1;
		else if (c == 'r')
			g_r = 1;
		else if (c == 't')
			g_t = 1;
	}
}

int			main(int argc, char **argv)
{
	t_opt			opt;

	g_a = 0;
	g_l = 0;
	g_re = 0;
	g_r = 0;
	g_t = 0;
	g_p = 0;
	if (argc == 1)
		ls_l(".");
	else
	{
		get_opt_assi(argc, argv, &opt);
		if (argc == opt.nb)
		{
			ls_l(".");
			return (0);
		}
		arg_to_tab(argc - opt.nb, argv + opt.nb);
	}
	return (0);
}
