
#include "libft.h"

static void	   sort(void **tab, int bg, int ed, int (*f)(void *, void *))
{
	void		*pvt = tab[bg];
	int			lft;
	int			rgt;

	lft = bg - 1;
	rgt = ed + 1;
	if (bg >= ed)
		return ;
	while (1)
	{
		while (f(tab[--rgt], pvt) > 0)
			;
		while (f(tab[++lft], pvt) < 0)
			;
		if (lft < rgt)
			ft_swap(&tab[lft], &tab[rgt]);
		else
			break ;
	}
	sort(tab, bg, rgt, f);
	sort(tab, rgt + 1, ed, f);
}

void	   ft_sort_qck(void **tab, int size, int (*f)(void *, void *))
{
	sort(tab, 0, size - 1, f);
}
