
#include "libft.h"

void	*ft_malloc (size_t n)
{
	void	*ret;

	if(!(ret = malloc(n)))
	{
		ft_putstr_fd("Malloc error: Program quited.", 2);
		exit (EXIT_FAILURE);
	}
	return (ret);
}
