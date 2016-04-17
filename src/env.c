/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:28:25 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/17 22:50:13 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_command_flags(char *mode, char **arg)
{
	if (ft_strcmp(arg[1], "-") == 0
			|| ft_strcmp(arg[1], "--ignore-environment") == 0
			|| ft_strcmp(arg[1], "-i") == 0)
	{
		*mode = 'i';
		if (arg[2] == NULL)
			return (-1);
	}
	else if ((ft_strcmp(arg[1], "-u") == 0
			|| ft_strcmp(arg[1], "--unset") == 0)
			&& arg[2] != NULL)
		*mode = 'u';
	else
	{
		ft_printf("env: illegal option -- %s\n usage: env [[-, -i, %s",
		"--ignore-environment] [-u name, --unset name]] [command [args...]]\n",
			arg[1]);
		return (-1);
	}
	return (0);
}

char		**ft_env_command(char *mode, int len, char **arg, char ***env)
{
	if (len > 1)
	{
		if (arg[1][0] == '-'
			&& get_env_command_flags(mode, arg) == -1)
			return (NULL);
		return (arg);
	}
	else if (len == 1)
		ft_print_env(*env);
	else
		ft_printf("minishell: env: %s: No such file or directory.\n", arg[1]);
	return (NULL);
}

int			ft_get_in_env(char *search, char **env)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (env[i])
		if ((ret = ft_strstr((const char *)env[i++], search)) != NULL)
			return (i - 1);
	return (-1);
}

static void	ft_replace_by_env_var(char ***arg, char ***env, int i, int pos)
{
	int		len;
	char	*tmp;

	len = ft_strlen((*arg)[i]);
	if ((pos = ft_get_in_env(
		tmp = ft_strjoin((*arg)[i] + 1, "="), *env)) != -1)
	{
		ft_strdel((*arg) + i);
		(*arg)[i] = ft_strdup((*env)[pos] + len);
	}
	ft_strdel(&tmp);
}

void		ft_parse_args_for_env_var(char ***arg, char ***env)
{
	int		i;
	int		pos;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while ((*arg)[i])
	{
		if ((*arg)[i][0] == '$')
			ft_replace_by_env_var(arg, env, i, pos);
		else if ((*arg)[i][0] == '~')
		{
			if ((pos = ft_get_in_env("HOME=", *env)) != -1)
			{
				tmp = (*arg)[i];
				(*arg)[i] = ft_strjoin_free(ft_strdup((*env)[pos] + 5),
						ft_strdup(tmp + 1));
				ft_strdel(&tmp);
			}
			else
				ft_printf("minishell: set $HOME environment \
variable before using ~\n");
		}
		i++;
	}
}
