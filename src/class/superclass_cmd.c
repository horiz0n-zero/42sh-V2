
#include "shell.h"

static const t_hashb	g_hash_builtins[] =
{
	{built_env, "env"},
	{built_unsetenv, "unsetenv"},
	{built_setenv, "setenv"},
	{built_cd, "cd"},
	{built_echo, "echo"},
	{built_exit, "exit"},
	{built_exit, "quit"},
	{built_export, "export"},
	{NULL, NULL}
};

static t_fbuil		cmd_isbuilt(const char *split)
{
	const t_hashb	*array = (const t_hashb*)&g_hash_builtins;

	while (array->built)
	{
		if (compare(array->text, split))
			return (array->built);
		array++;
	}
	return (NULL);
}

static bool 		cmd_add_spec(t_cmd *const cmd, char **argv)
{
	cmd_redirection(cmd, argv);
	cmd_env(cmd, argv);
	return (true);
}

static void			cmd_add_argv(t_dispatch *const dispatch, t_cmd *const cmd,
		char **argv)
{
	void 					*path;

	path = dispatch->hashtable->get(dispatch->hashtable, *argv);
	cmd->argv = argv;
	if (path)
		*cmd->argv = path;
	else if ((path = cmd_isbuilt(*argv)))
		cmd->is_builtin = path;
	else if (!(**argv == '.' || **argv == '/'))
		cmd->is_ok = false;
	cmd_add_spec(cmd, cmd->argv);
}

void				*ft_cmd_ctor(const void *const self, ...)
{
	t_dispatch		*dispatch;
	va_list			args;
	t_cmd			*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	va_start(args, self);
	dispatch = va_arg(args, t_dispatch*);
	new->based_class = self;
	new->is_builtin = NULL;
	new->is_ok = true;
	new->stdin = STDIN_FILENO;
	new->stdout = STDOUT_FILENO;
	new->stderr = STDERR_FILENO;
	new->background = false;
	cmd_add_argv(dispatch, new, va_arg(args, char**));
	va_end(args);
	return (new);
}

void			ft_cmd_dtor(void *const self)
{
	t_cmd		*cmd;

	cmd = self;
	if (cmd->stdin != STDIN_FILENO)
		close(cmd->stdin);
	if (cmd->stdout != STDOUT_FILENO)
		close(cmd->stdout);
	if (cmd->stderr != STDERR_FILENO)
		close(cmd->stderr);
	free(cmd);
}
