/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:25:43 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/01 20:01:16 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_change_directory_core(char **arg, char ***env)
{
	int	old_pwd;

	if (ft_strcmp(arg[1], "-") == 0)
	{
		if ((old_pwd = ft_get_in_env("OLDPWD=", *env)) == -1)
			ft_printf("minishell: cd: OLDPWD not set\n");
		else
			ft_open_dir(*((*env) + old_pwd) + 7, env);
	}
	else if (access(arg[1], R_OK) == 0)
		ft_open_dir(arg[1], env);
	else
		ft_printf("minishell: cd: cannot access to path.\n");
}

void		ft_change_directory(char **arg, char ***env)
{
	int	i;

	i = -1;
	while (arg[++i])
		;
	if (i > 2)
		ft_printf("cd: string not in pwd: %s\n", arg[1]);
	else if (i > 1)
		ft_change_directory_core(arg, env);
	else
		ft_open_home_dir(*env);
}

int			ft_open_home_dir(char **env)
{
	int	i;

	i = 0;
	if ((i = ft_get_in_env("HOME=", env)) != -1)
	{
		if (chdir((const char *)env[i] + 5) == -1)
			ft_printf("CHDIR Error\n");
		else
			return (0);
	}
	else
		ft_printf("minishell: $HOME is not set.\n");
	return (-1);
}

void		ft_open_dir(char *dir, char ***env)
{
	char	**arg;
	int		i;
	char	cwd[1024];

	i = 0;
	getcwd(cwd, sizeof(cwd));
	if (chdir((const char *)dir) == -1)
		ft_printf("minishell: cd: directory does not exist: %s\n", dir);
	else
	{
		if ((arg = (char **)malloc(sizeof(char *) * (3))) == NULL)
		{
			ft_printf("minishell: malloc: cannot allocate memory.\n");
			exit(-1);
		}
		arg[0] = ft_strdup("setenv");
		arg[1] = ft_strdup("OLDPWD");
		arg[2] = ft_strdup(cwd);
		arg[3] = NULL;
		ft_modify_env(arg, env, 1);
		while (arg[i])
			ft_strdel(arg + i++);
		free((void *)arg);
		arg = NULL;
	}
}
