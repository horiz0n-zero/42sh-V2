/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 21:01:01 by afeuerst          #+#    #+#             */
/*   Updated: 2017/04/25 13:35:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H

# define UTILITY_H

# include "shell.h"

void	ft_memset(int8_t *ptr, const int8_t value, size_t len);
void	ft_memset_ll(int64_t *ptr, const int64_t value, size_t len);
int		ft_strlen_i(const char *str);
size_t	ft_strlen_s(const char *str);
size_t	ft_strlen_sm(const char *str, const char c);
int		ft_strlen_im(const char *str, const char c);
size_t	ft_strlen_magik(const char *str, const char c);
void	ft_memmove(int8_t *dst, const int8_t *src, size_t len);
char	**ft_strsplit(char *str, int (*f)(int));
char	*ft_strsub(const char *src);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strcjoin(const char *s1, const char *s2, const char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
bool	compare(const char *s1, const char *s2);
int		ft_isspace(const int c);
int		ft_isdoublepoint(const int c);
void	ft_strinjoin(const char *s1, const char *s2, char *in);
char	*ft_strincjoin(const char *s1, const char *s2, const char c, char *in);
char 	*ft_itoa_base(int nb, const int base);
int 	ft_atoi(const char *str);

void	ft_minishell(void);

# define COPY(str) ft_strsub(str)
# define JOIN(s1, s2) ft_strjoin(s1, s2)
# define CJOIN(s1, s2, c) ft_strcjoin(s1, s2, c)
# define SPLIT(str, func) ft_strsplit(str, func)
# define LENI(str) ft_strlen_i(str)
# define LENS(str) ft_strlen_s(str)
# define LENMS(str, c) ft_strlen_sm(str, c)
# define LENMI(str, c) ft_strlen_im(str, c)

#endif
