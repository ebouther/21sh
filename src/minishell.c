/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 17:37:30 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/29 14:27:09 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_in_env(char *search, char **env)
{
	int	i;
	char *ret;

	i = 0;
	ret = NULL;
	while (env[i])
		if ((ret = ft_strstr((const char *)env[i++], search)) != NULL)
			return (i - 1);
	return (-1);
}

static char	**ft_get_user_input(pid_t pid)
{
	char	**arg;
	char	*str;

	arg = NULL;
	if (get_next_line(1, &str))
	{
		if (ft_strlen((char *)(arg = ft_strsplit(str, ' '))) > 0)
		{
			if (ft_strcmp(arg[0], "exit") == 0)
			{
				kill(pid, SIGKILL);
			}
			else if (ft_strcmp(arg[0], "cd") == 0)
			{
				ft_printf("CD\n");
			}
			return (arg);
		}
	}
	return (NULL);
}

static void	ft_find_and_exec_bin(char **input, char **env)
{
	char	*path;
	char	**split;
	int		i;

	if ((i = ft_get_in_env("PATH=", env)) != -1)
	{
		split = ft_strsplit(env[i], ':');
		while (*split != '\0')
		{
			if (access(path = ft_strjoin(*split, ft_strjoin("/", input[0])), X_OK) == 0)
				execve(path, ft_strlen((char *)input) > 1 ? input : NULL, NULL);
			split++;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	char	**input;

	(void)ac;
	(void)av;

	while (42)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_printf("$> ");
			if ((input = ft_get_user_input(pid)) != NULL)
				ft_find_and_exec_bin(input, env);
		}
		else if (pid > 0)
			wait(NULL);
		else
		{
			ft_printf("Fork error.\n");
			exit(-1);
		}
	}
	return (0);
}
