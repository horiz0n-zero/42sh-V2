/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 21:19:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/25 14:04:40 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

void			ft_catching_signal(void);
void			ft_default_signal(void);

int 			kill(pid_t pid, int sig);

int 			setpgid(pid_t pid, pid_t pgid_t);
# ifdef str_error
#  undef str_error
# endif

const char		*str_error(const int signal);

typedef void 	(*t_signal_function)(void);

#endif
