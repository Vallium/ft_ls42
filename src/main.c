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
	ft_putstr_fd("usage: ft_ls [-RSalprt1] [file ...]\n", 2);
}

int			arg_cmp(void *na1, void *na2)
{
	return (ft_strcmp(na1, na2));
}

void		get_opt_assi(int argc, char **argv, t_opt *opt)
{
	char	c;

	opt->optstr = "RSagloprt1";
	opt->nb = 1;
	while ((c = ft_get_opt(argc, argv, opt)) > 0)
	{
		if (c == '?')
		{
			ft_putstr_fd("ft_ls: illegal option -- ", 2),
			ft_putchar_fd(opt->err, 2),
			ft_putchar_fd('\n', 2),
			usage(),
			exit (2);
		}
		g_l = (c == 'l') ? 1 : g_l;
		g_re = (c == 'R') ? 1 : g_re;
		g_ss = (c == 'S') ? 1 : g_ss;
		g_a = (c == 'a') ? 1 : g_a;
		g_p = (c == 'p') ? 1 : g_p;
		g_r = (c == 'r') ? 1 : g_r;
		g_t = (c == 't') ? 1 : g_t;
		g_g = (c == 'g') ? 1 : g_g;
		g_o = (c == 'o') ? 1 : g_o;
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
	g_ss = 0;
	g_g = 0;
	g_o = 0;
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
