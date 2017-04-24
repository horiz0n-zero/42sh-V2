#include "shell.h"

void		foreground_exec(t_dispatch *const dispatch, char *buffer)
{
	t_cmd 	*cmd;

	cmd = ((t_class*)dispatch->foreground->based_class_cmd)->ctor(NULL, dispatch, buffer);
	dispatch->foreground->execute(dispatch, cmd);
}
