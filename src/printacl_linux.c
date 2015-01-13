
#include "ft_ls.h"

void		print_acl_attr(t_file **file, int i, char *arg)
{
	if (listxattr(ft_burger(arg, '/', file[i]->name), NULL, 256) > 0)
		ft_putstr("@ ");
	//else if (acl_get_link_np(ft_burger(arg, '/', file[i]->name),
	//									ACL_TYPE_EXTENDED))
	//	ft_putstr("+ ");
	else
		ft_putstr("  ");
}
