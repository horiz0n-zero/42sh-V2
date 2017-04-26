
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

static t_fbuil		cmd_isbuilt(t_cmd *const cmd, char **split)
{
	const t_hashb	*array = (const t_hashb*)&g_hash_builtins;

	while (array->built)
	{
		if (compare(array->text, *split))
		{
			cmd->argv = split;
			return (array->built);
		}
		array++;
	}
	cmd->argv = split;
	return (NULL);
}

static bool 		cmd_add_spec(t_cmd *const cmd, char **argv)
{
	cmd_redirection(cmd, argv);
	cmd_env(cmd, argv);
	return (true);
}

static void			cmd_add_argv(t_dispatch *const dispatch, t_cmd *const cmd,
		char **split)
{
	char			*path;

	if (!split || !*split)
	{
		cmd->is_ok = false;
		return ;
	}
	cmd_add_spec(cmd, split);
	if (*split && (**split == '.' || **split == '/'))
	{
		(cmd->is_ok = true) && (cmd->argv = split);
		return ;
	}
	path = dispatch->hashtable->get(dispatch->hashtable, *split);
	if (!path)
	{
		if (!(cmd->is_builtin = cmd_isbuilt(cmd, split)))
			cmd->is_ok = false;
		else
			cmd->is_ok = true;
		return ;
	}
	*split = path;
	cmd->argv = split;
	cmd->is_ok = true;
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
	new->is_illegal = false;
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