/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:13:33 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/13 22:21:44 by afeuerst         ###   ########.fr       */
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
# include <term.h>
# include <termios.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>

# include <pthread.h>

# include "utility.h"
# include "signal.h"


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
typedef struct s_cmd		t_cmd;
typedef struct s_environ	t_environ;
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

struct				s_environ
{
	const void		*based_class;
	void			(*get_required)(void);
	int				(*modify)(const char *key, const char *value);
	int				(*remove)(const char *key);
	void			(*append)(const char *full_value);
};

void				*ft_environ_ctor(const void *const self, ...);
void				ft_environ_dtor(void *const self);

typedef struct		s_guard_struct
{
	size_t			len;
	char			*string;
	char			*(*get)(const struct s_guard_struct guard);
}					t_guard_struct;

void				env_guard(void);
char				*guard_term(const t_guard_struct guard);
char				*guard_path(const t_guard_struct guard);
char				*guard_pwd(const t_guard_struct guard);
char				*guard_shlvl(const t_guard_struct guard);
char				*guard_underscore(const t_guard_struct guard);

void				env_get_default(void);
size_t				env_count(void);
int					env_remove(const char *key);
void				env_append(const char *full_value);

/*
** struct s_cmd { }; superclass
*/

typedef void		(*t_fbuiltins)(void *const self);

struct				s_cmd
{
	const void		*based_class;
	char			**args;
	t_fbuiltins		builtin;
};
void				*ft_cmd_ctor(const void *const self, ...);
void				ft_cmd_dtor(void *const self);

/*
** struct s_dispatch { }; subclass
*/

typedef void		(*t_fdis)(t_dispatch *const dispatch);

struct				s_dispatch
{
	const void		*based_class;
	t_display		*display;
	t_environ		*environ;
	pthread_t		thread[2];
	pthread_attr_t	attribute;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	void			(*start)(t_dispatch *const dispatch);
};
void				*ft_dispatch_ctor(const void *const self, ...);
void				ft_dispatch_dtor(void *const self);

void				ft_start(t_dispatch *const dispatch);

/*
** PTHREAD routines
*/

typedef void		*(*t_task)(void *argument);

void				*task_display_init(void *arg);
void				*task_environ_init(void *arg);
#endif
