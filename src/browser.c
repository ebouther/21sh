/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:25:43 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/31 19:32:29 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_open_home_dir(char **env)
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

void	ft_open_dir(char *dir, char ***env)
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
