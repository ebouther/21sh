/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:35:00 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/18 22:38:28 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_switch_builtin_command_2(char *mode, int len,
											char **arg, char ***env)
{
	if (ft_strcmp(arg[0], "env") == 0)
		return (ft_env_command(mode, len, arg, env));
	else if (ft_strcmp(arg[0], "unsetenv") == 0)
	{
		if (len > 1)
			ft_modify_env(arg, env, 0);
		else
			ft_printf("minishell: unsetenv: not enough arguments.\n");
	}
	else if (ft_strcmp(arg[0], "cd") == 0)
		ft_change_directory(arg, env);
	else if (ft_strcmp(arg[0], "clear") == 0)
		ft_printf("\033[2J\033[1;1H");
	else
		return (arg);
	return (NULL);
}

static char	**ft_switch_builtin_command(char *mode, int len, char **arg,
		char ***env)
{
	if (ft_strcmp(arg[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(arg[0], "setenv") == 0)
	{
		if (len > 3)
			ft_printf("minishell: setenv: Too many arguments.\n");
		else if (len > 1)
		{
			if (ft_isalpha(arg[1][0]) == 0)
				ft_printf("minishell: setenv: %s",
					"Variable name must begin with a letter.\n");
			else
				ft_modify_env(arg, env, 1);
		}
		else if (len == 1)
			ft_print_env(*env);
	}
	else
		return (ft_switch_builtin_command_2(mode, len, arg, env));
	return (NULL);
}

char		**ft_get_user_input(char *mode, char ***env)
{
	t_input	i;

	i.arg = NULL;
	if (get_next_line(1, &i.str) && ft_strcmp(i.str, "") != 0)
	{
		if ((i.arg = ft_strsplit(i.str, ' ')) != NULL)
		{
			ft_parse_args_for_env_var(&i.arg, env);
			i.len = 0;
			while (i.arg[i.len])
				i.len++;
			if ((i.ret = ft_switch_builtin_command(
				mode, i.len, i.arg, env)) != NULL)
			{
				ft_strdel(&i.str);
				return (i.ret);
			}
			i.n = 0;
			while (i.arg[i.n])
				ft_strdel(i.arg + i.n++);
			ft_memdel((void **)&(i.arg));
		}
		ft_strdel(&i.str);
	}
	return (NULL);
}
