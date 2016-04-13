/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 17:39:03 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/13 21:44:09 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include "libft.h"

typedef struct	s_main
{
	pid_t	pid;
	char	**input;
	int		i;
	char	mode;
}				t_main;

typedef struct	s_input
{
	char		**ret;
	char		**arg;
	char		*str;
	int			len;
	int			n;
}				t_input;

typedef struct	s_new_env
{
	char		**new_env;
	char		*search;
	int			search_len;
	int			len;
	int			i;
	int			n;
}				t_new_env;

typedef struct	s_unset_env
{
	int			pos;
	int			len;
	int			i;
	int			n;
	char		**new_env;
	char		*tmp;
}				t_unset_env;

typedef struct	s_setenv
{
	int			len;
	int			pos;
	char		**new_env;
	char		*tmp;
}				t_setenv;

/*
** builtin.c
*/
void			ft_modify_env(char **arg, char ***env, int mode);
void			ft_print_env(char **env);

/*
** browser.c
*/
void			ft_open_dir(char *dir, char ***env);
int				ft_open_home_dir(char **env);
void			ft_change_directory(char **arg, char ***env);

/*
** env.c
*/
char			**ft_env_command(char *mode, int len, char **arg, char ***env);
int				ft_get_in_env(char *search, char **env);
void			ft_parse_args_for_env_var(char ***arg, char ***env);

/*
** input.c
*/
char			**ft_get_user_input(char *mode, char ***env);

#endif
