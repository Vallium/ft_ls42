int        cmp(void *a, void *b)
{
    int ia = *((int*)a);
    int ib = *((int*)b);
    if (ia < ib)
        return(-1);
    if (ia > ib)
        return(1);
    return(0);
}

void swap(void **p1, void **p2)
{
    void	*tmp;

    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void	   sort(void **tab, int bg, int ed, int (*f)(void *, void *))
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
            swap(&tab[lft], &tab[rgt]);
        else
            break ;
    }
    sort(tab, bg, rgt, f);
    sort(tab, rgt + 1, ed, f);
}

void	   ft_q_sort(void **tab, int size, int (*f)(void *, void *))
{
    sort(tab, 0, size - 1, f);
}


int main (void)
{
    int tab[] = {8,12,89,21,64,1,5,8,54,6,5,21,54,78,0};
    int *tab2[15];
    int tab3[15];
    int   i;

    for ( i=0; i< 15; i++)
        tab2[i] = &tab[i];
    ft_q_sort((void**)tab2, 15, cmp);

    for ( i=0; i< 15; i++)
        tab3[i] = *tab2[i];
    return 0;
}
