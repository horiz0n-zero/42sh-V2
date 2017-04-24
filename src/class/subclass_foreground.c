
#include "shell.h"

static const t_class g_description_cmd =
{
	sizeof(t_cmd), ft_cmd_ctor, ft_cmd_dtor
};

static void 		ft_initialize_forground(t_foreground *const fg)
{
	pid_t 			group;

	if (isatty(STDIN_FILENO))
	{
		while (tcgetpgrp(STDIN_FILENO) != (group = getpgrp()))
			kill(group, SIGTTIN);
		ft_catching_signal();
		group = getpid();
		if (setpgid(group, group) < 0)
			exit(1);
		tcsetpgrp(STDIN_FILENO, group);
		fg->groupid = group;
	}
	else
		exit(1);
}

void				*ft_foreground_ctor(const void *const self, ...)
{
	t_foreground 	*new;

	new = malloc(sizeof(t_foreground));
	if (!new)
		return (new);
	new->based_class = self;
	new->based_class_cmd = &g_description_cmd;
	new->exec = foreground_exec;
	new->execute = foreground_execute;
	ft_initialize_forground(new);
	return (new);
}

void 				ft_foreground_dtor(void *const self)
{
	free(self);
}
