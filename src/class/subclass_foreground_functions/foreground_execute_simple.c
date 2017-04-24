
#include "shell.h"

int		 		foreground_execute(t_dispatch *const dispatch, t_cmd *const cmd)
{
	pid_t	 	child;
	int 		status;
	extern char **environ;

	status = 0;
	if (cmd->is_ok == false)
	{
		print("\e[33mCommand not found: %s\n", 1, *cmd->argv);
		return (0);
	}
	child = fork();
	if (!child)
	{
		if (cmd->is_builtin)
			cmd->is_builtin(dispatch, cmd->argv);
		else
			execve(*cmd->argv, cmd->argv, environ);
	}
	else
		waitpid(child, &status, 0);
	return (status);
}
