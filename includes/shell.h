/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:13:33 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/22 16:14:14 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <term.h>
# include <time.h>
# include <termios.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <sys/utsname.h>
# include <pthread.h>

# include "utility.h"
# include "signal.h"
# include "print.h"

/*
** struct s_class { }; based_class
*/

typedef struct		s_class
{
	size_t			size;
	void			*(*ctor)(const void *const self, ...);
	void			(*dtor)(void *const self);
}					t_class;

typedef struct s_display	t_display;
typedef struct s_dispatch	t_dispatch;
typedef struct s_environ	t_environ;
typedef struct s_hashable	t_hashable;

/*
** struct s_display { }; superclass
*/

# define MAX_DISPLAY_CHAR 8096

struct				s_display
{
	const void		*based_class;
	struct termios	origin;
	struct termios	term;
	struct winsize	screen;
	struct utsname	name;
	int				prompt_pos;
	int				index;
	char			buffer[MAX_DISPLAY_CHAR];
	void			(*apply)(int32_t nb, ...);
	void			(*prompt)(t_dispatch *const dispatch, const int32_t target);
	void			(*set_8)(const int8_t value, t_dispatch *const dispatch);
	void			(*set_24)(const int8_t value, t_dispatch *const dispatch);
	void			(*push_byte)(t_dispatch *const dispatch, const int8_t c);
	void			(*unpush_byte)(t_dispatch *const dispatch);
	void			(*mx)(t_dispatch *const dispatch, int x, const int n);
	void			(*my)(t_dispatch *const dispatch, int y, const int n);
};
void				*ft_display_ctor(const void *const self, ...);
void				ft_display_dtor(void *const self);

int					ft_putchar(int signal);

void				ft_set8(const int8_t value, t_dispatch *const dispatch);
void				ft_set24(const int8_t value, t_dispatch *const dispatch);
void				ft_push_byte(t_dispatch *const dispatch, const int8_t c);
void				ft_unpush_byte(t_dispatch *const dispatch);
void				ft_delete(t_dispatch *const dispatch);
void				ft_clear(t_dispatch *const dispatch);
void				ft_move_left(t_dispatch *const dispatch);
void				ft_move_right(t_dispatch *const dispatch);
void				ft_arrow_up(t_dispatch *const dispatch);
void				ft_arrow_down(t_dispatch *const dispatch);
void				ft_mx(t_dispatch *const dispatch, int x, const int n);
void				ft_my(t_dispatch *const dispatch, int y, const int n);

# define GO_LEFT  0b00000001
# define GO_RIGHT 0b00000010
# define GO_UP    0b00000001
# define GO_DOWN  0b00000010
# define PR_SUCCESS 1
# define PR_FAILED  2
# define PR_QUOTES  3

void				ft_prompt(t_dispatch *const dispatch, const int32_t target);
typedef void		(*t_fpr)(t_dispatch *const dispatch, char *const buffer);

/*
** struct s_environ { }; superclass
*/

# define ENV_SPACE_AVAILABLE 5

struct				s_environ
{
	const void		*based_class;
	size_t			(*count)(size_t default_value);
	size_t			size;
	size_t			sort_type;
	void			(*get_required)(t_environ *const environ);
	int				(*modify)(const char *key, const char *value);
	int				(*remove)(t_environ *const env, const char *key);
	void			(*append)(t_environ *const env, const char *full_value);
	void			(*expand)(t_environ *const env, const size_t count);
	const char		*(*value)(const char *key);
	void 			(*kill)(void);
	void			(*sort)(const int count, char **array, const int func);
};
void				*ft_environ_ctor(const void *const self, ...);
void				ft_environ_dtor(void *const self);

void				env_get_default(t_environ *const env);
size_t				env_count(void);
int					env_remove(t_environ *const env, const char *key);
void				env_append(t_environ *const env, const char *full_value);
void				env_expand(t_environ *const env, const size_t count);
void 				env_kill(void);
int 				env_modify(const char *key, const char *value);
typedef int			(*const f_sort)(char*, char*);
void				env_sshell(const int count, char **array, const int func);
# define F_ASCII 0
# define F_REV_ASCII 1
# define F_UNKNOW 2
# define IVALUE *(array + i)
# define JVALUE *(array + j)

typedef struct		s_guard_struct
{
	size_t			len;
	char			*string;
	char			*(*get)(const struct s_guard_struct guard);
}					t_guard_struct;

void				env_guard(t_environ *const env);
char				*guard_home(const t_guard_struct guard);
char				*guard_term(const t_guard_struct guard);
char				*guard_path(const t_guard_struct guard);
char				*guard_pwd(const t_guard_struct guard);
char				*guard_shlvl(const t_guard_struct guard);
char				*guard_underscore(const t_guard_struct guard);
# define GUARD_COUNT 7

/*
** struct hashable { }; subclass
*/

struct				s_hashable
{
	const void		*based_class;
	char			**array;
	size_t			size;
	size_t			(*key)(const char *key);
	void			(*set)(t_hashable *const hash, const char *key, char *data);
	char			*(*get)(t_hashable *const hash, const char *key);
	void			(*rm)(t_hashable *const hash, int n, ...);
	void			(*refresh)(t_dispatch *const dispatch);
};
void				*ft_hashable_ctor(const void *const self, ...);
void				ft_hashable_dtor(void *const self);

void				ft_hash_rm(t_hashable *const hash, int n, ...);
size_t				ft_bin_count(const t_environ *const env);
void				hash_fill(t_hashable *const hash, t_environ *const env);
void				hash_refresh(t_dispatch *const dispatch);

/*
** struct s_dispatch { }; subclass
*/

typedef void		(*t_fdis)(t_dispatch *const dispatch);

struct				s_dispatch
{
	const void		*based_class;
	t_display		*display;
	t_environ		*environ;
	t_hashable		*hashtable;
	pthread_t		thread[4];
	pthread_attr_t	attribute;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	void			(*start)(t_dispatch *const dispatch);
};
void				*ft_dispatch_ctor(const void *const self, ...);
void				ft_dispatch_dtor(void *const self);

void				ft_start(t_dispatch *const dispatch);

/*
** builtins
*/
# define BUILTINS_COUNT 7

typedef int			(*const t_fbuil)(t_dispatch *const dispatch, char **argv);
typedef struct		s_hashb
{
	t_fbuil			built;
	const char		*const text;
}					t_hashb;

int 				built_export(t_dispatch *const dispatch, char **argv);
int					built_env(t_dispatch *const dispatch, char **argv);
int					env_n(t_dispatch *const dispatch, char **argv);
int					env_a(t_dispatch *const dispatch, char **argv);
int					env_r(t_dispatch *const dispatch, char **argv);
int					env_i(t_dispatch *const dispatch, char **argv);
int					built_unsetenv(t_dispatch *const dispatch, char **argv);
int					built_setenv(t_dispatch *const dispatch, char **argv);
int					built_cd(t_dispatch *const dispatch, char **argv);
int					built_echo(t_dispatch *const dispatch, char **argv);
int					built_exit(t_dispatch *const dispatch, char **argv);

/*
** pthread
*/

typedef void		*(*t_task)(void *argument);
void				*task_display_init(void *arg);
void				*task_environ_init(void *arg);
void				*task_hashable_init(void *arg);
#endif
