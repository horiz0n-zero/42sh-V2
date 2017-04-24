
#include "shell.h"

int		built_export(t_dispatch *const dispatch, char **argv)
{	
	argv++;
	if (argv && *argv)
	{
		while (*argv)
			dispatch->environ->append(dispatch->environ, *argv++);
	}
	else
		print("\e[36mexport [ $VALUE ... ]\n\e[37m", 0);
	return (0);
}
