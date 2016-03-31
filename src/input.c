/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:35:00 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/31 19:50:02 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_switch_builtin_command_2(int len, char **arg, char ***env)
{
	if (ft_strcmp(arg[0], "env") == 0)
	{
		if (len == 1)
			ft_print_env(*env);
		else
			ft_printf("minishell: env: %s: No such file or directory.\n", arg[1]);
	}
	else if (ft_strcmp(arg[0], "cd") == 0)
		ft_change_directory(arg, env);
	else if (ft_strcmp(arg[0], "clear") == 0)
		ft_printf("\033[2J\033[1;1H");
	else
		return (arg);
	return (NULL);
}

static char	**ft_switch_builtin_command(int len, char **arg, char ***env)
{
	if (ft_strcmp(arg[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(arg[0], "unsetenv") == 0)
	{
		if (len > 1)
			ft_modify_env(arg, env, 0);
		else
			ft_printf("minishell: unsetenv: not enough arguments.\n");
	}
	else if (ft_strcmp(arg[0], "setenv") == 0)
	{
		if (len > 2)
		{
			if (ft_isalpha(arg[1][0]) == 0)
				ft_printf("minishell: setenv: Variable name must begin with a letter.\n");
			else
				ft_modify_env(arg, env, 1);
		}
		else if (len == 1)
			ft_print_env(*env);
	}
	else
		return (ft_switch_builtin_command_2(len, arg, env));
	return (NULL);
}

char	**ft_get_user_input(char ***env)
{
	char	**ret;
	char	**arg;
	char	*str;
	int		len;
	int		i;

	arg = NULL;
	if (get_next_line(1, &str) && ft_strcmp(str, "") != 0)
	{
		if ((arg = ft_strsplit(str, ' ')) != NULL)
		{
			ft_parse_args_for_env_var(&arg, env);
			len = 0;
			while (arg[len])
				len++;
			if ((ret = ft_switch_builtin_command(len, arg, env)) != NULL)
			{
				ft_strdel(&str);
				return (ret);
			}
			i = 0;
			while (arg[i])
				ft_strdel(arg + i++);
			free((void *)arg);
			arg = NULL;
		}
		ft_strdel(&str);
	}
	return (NULL);
}
