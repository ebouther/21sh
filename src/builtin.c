/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:20:29 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/31 19:33:20 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_change_directory(char **arg, char ***env)
{
	int	i;
	int	old_pwd;

	i = -1;
	while (arg[++i])
		;
	if (i > 2)
		ft_printf("cd: string not in pwd: %s\n", arg[1]);
	else if (i > 1)
	{
		if (ft_strcmp(arg[1], "-") == 0)
		{
			if ((old_pwd = ft_get_in_env("OLDPWD=", *env)) == -1)
				ft_printf("minishell: cd: OLDPWD not set\n");
			else
				ft_open_dir(*((*env) + old_pwd) + 7, env);
		}
		else if (ft_strcmp(arg[1], "~") == 0)
			ft_open_home_dir(*env);
		else if (access(arg[1], R_OK) == 0)
			ft_open_dir(arg[1], env);
		else
			ft_printf("minishell: cd: cannot access to path.\n");
	}
	else
		ft_open_home_dir(*env);
}

static void	ft_setenv(char **arg, char ***env, int *modified)
{
	int		len;
	int		i;
	char	*tmp;
	char	**new_env;
	int		pos;

	pos = ft_get_in_env(tmp = ft_strjoin_free(ft_strdup(arg[1]), ft_strdup("=")), *env);
	len = 0;
	while ((*env)[len])
		len++;
	if ((new_env = (char **)malloc(sizeof(char *) * (len + ((pos == -1) ? 1 : 0) + 1))) == NULL)
	{
		ft_printf("minishell: malloc: cannot allocate memory.\n");
		exit(-1);
	}
	i = 0;
	while ((*env)[i])
	{
		if (i == pos)
			new_env[i] = ft_strjoin_free(ft_strdup(tmp), ft_strdup(arg[2]));
		else
			new_env[i] = ft_strdup((*env)[i]);
		if (*modified == 1)
			ft_strdel((*env) + i);
		i++;
	}
	if (*modified == 1)
		free((void *)(*env));
	if (pos == -1)
		new_env[len] = ft_strjoin_free(ft_strdup(tmp), ft_strdup(arg[2]));
	new_env[len + ((pos == -1) ? 1 : 0)] = NULL;
	(*env) = new_env;
	*modified = 1;
	ft_strdel(&tmp);
}

static void	ft_unset_env(char **arg, char ***env, int *modified)
{
	int		pos;
	int		len;
	int		i;
	int		n;
	char	**new_env;
	char	*tmp;

	if ((pos = ft_get_in_env(tmp = ft_strjoin_free(ft_strdup(arg[1]),
			ft_strdup("=")), *env)) != -1)
	{
		len = 0;
		while ((*env)[len])
			len++;
		if ((new_env = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		{
			ft_printf("minishell: malloc: cannot allocate memory.\n");
			exit(-1);
		}
		i = 0;
		n = 0;
		while ((*env)[i])
		{
			if (i != pos)
			{
				new_env[n] = ft_strdup((*env)[i]);
				if (*modified == 1)
					ft_strdel(*env + i);
				n++;
			}
			i++;
		}
		if (*modified == 1)
			free((void *)(*env));
		new_env[n] = NULL;
		*env = new_env;
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

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
}
