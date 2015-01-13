/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 11:13:40 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/20 20:52:42 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		usage(void)
{
	ft_putstr_fd("usage: ft_ls [-RSadgloprtu1] [file ...]\n", 2);
}

int			arg_cmp(void *na1, void *na2)
{
	return (ft_strcmp(na1, na2));
}

void		illegal_option(t_opt *opt)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2),
	ft_putchar_fd(opt->err, 2),
	ft_putchar_fd('\n', 2),
	usage(),
	exit (2);
}

void		get_opt_assi(int argc, char **argv, t_opt *opt)
{
	char	c;

	opt->optstr = "RSadgloprtu1";
	opt->nb = 1;
	while ((c = ft_get_opt(argc, argv, opt)) > 0)
	{
		if (c == '?')
			illegal_option(opt);
		g_l = (c == 'l') ? 1 : g_l;
		g_l = (c == '1') ? 0 : g_l;
		g_re = (c == 'R') ? 1 : g_re;
		g_ss = (c == 'S') ? 1 : g_ss;
		g_a = (c == 'a') ? 1 : g_a;
		g_p = (c == 'p') ? 1 : g_p;
		g_r = (c == 'r') ? 1 : g_r;
		g_t = (c == 't') ? 1 : g_t;
		g_g = (c == 'g') ? 1 : g_g;
		g_o = (c == 'o') ? 1 : g_o;
		g_u = (c == 'u') ? 1 : g_u;
		g_d = (c == 'd') ? 1 : g_d;
		g_l = (c == 'g' || c == 'o') ? 1 : g_l;
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
			(g_d && !g_l) ? ft_putstr(".\n") : ls_l(".");
			return (0);
		}
		arg_to_tab(argc - opt.nb, argv + opt.nb);
	}
	return (0);
}
