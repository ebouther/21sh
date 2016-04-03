/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:20:29 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/03 17:24:57 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_new_env(char **arg, char ***env, int *modified, t_setenv *s)
{
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (i == s->pos)
			s->new_env[i] = ft_strjoin_free(ft_strdup(s->tmp),
					ft_strdup(arg[2]));
		else
			s->new_env[i] = ft_strdup((*env)[i]);
		if (*modified == 1)
			ft_strdel((*env) + i);
		i++;
	}
}

static void	ft_setenv(char **arg, char ***env, int *modified)
{
	t_setenv	s;

	s = (t_setenv) {.len = 0, .pos = 0, .tmp = NULL, .new_env = NULL};
	s.pos = ft_get_in_env(
		s.tmp = ft_strjoin_free(ft_strdup(arg[1]), ft_strdup("=")), *env);
	while ((*env)[s.len])
		s.len++;
	if ((s.new_env = (char **)malloc(sizeof(char *)
			* (s.len + ((s.pos == -1) ? 1 : 0) + 1))) == NULL)
		ft_error_exit("minishell: malloc: cannot allocate memory.\n");
	ft_new_env(arg, env, modified, &s);
	if (*modified == 1)
		free((void *)(*env));
	if (s.pos == -1)
		s.new_env[s.len] = ft_strjoin_free(ft_strdup(s.tmp), ft_strdup(arg[2]));
	s.new_env[s.len + ((s.pos == -1) ? 1 : 0)] = NULL;
	(*env) = s.new_env;
	*modified = 1;
	ft_strdel(&s.tmp);
}

static void	ft_unset_env(char **arg, char ***env, int *modified)
{
	t_unset_env u;

	u = (t_unset_env){.len = 0, .i = -1, .n = 0};
	if ((u.pos = ft_get_in_env(
			u.tmp = ft_strjoin_free(ft_strdup(arg[1]),
			ft_strdup("=")), *env)) != -1)
	{
		while ((*env)[u.len])
			u.len++;
		if ((u.new_env = (char **)malloc(sizeof(char *) * (u.len + 1))) == NULL)
			ft_error_exit("minishell: malloc: cannot allocate memory.\n");
		while ((*env)[++(u.i)])
			if (u.i != u.pos)
			{
				u.new_env[u.n] = ft_strdup((*env)[u.i]);
				if (*modified == 1)
					ft_strdel(*env + u.i);
				u.n++;
			}
		if (*modified == 1)
			ft_memdel((void **)(env));
		u.new_env[u.n] = NULL;
		*env = u.new_env;
		*modified = 1;
	}
}

void		ft_modify_env(char **arg, char ***env, int mode)
{
	static int	modified = 0;

	if (mode == 1)
		ft_setenv(arg, env, &modified);
	else
		ft_unset_env(arg, env, &modified);
}

void		ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
}
