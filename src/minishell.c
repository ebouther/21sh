/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 17:37:30 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/03 15:10:14 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_search_in_path(int i, char **input, char **env, char **execve_env)
{
	char	**split;
	char	*path;
	char	*path_content;

	if ((path_content = ft_strchr((env)[i], '=')) != NULL)
		split = ft_strsplit(path_content + 1, ':');
	else
		return ;
	i = 0;
	while (split[i] != '\0')
	{
		if (access(path = ft_strjoin_free(ft_strdup(split[i]), ft_strjoin_free(
						ft_strdup("/"), ft_strdup(input[0]))), X_OK) == 0
				&& execve(path, input, execve_env) == -1)
			ft_printf("minishell: execve: cannot be executed.\n");
		ft_strdel(&path);
		i++;
	}
	i = 0;
	if (split != NULL)
		while (split[i])
			ft_strdel(split + i++);
}

static char	**ft_new_env(char **input, char **env)
{
	char	**new_env;
	char	*search;
	int		search_len;
	int		len;
	int		i;
	int		n;

	search_len = ft_strlen((search = ft_strjoin_free(ft_strdup(input[0]), ft_strdup("="))));
	len = 0;
	while (env[len])
		len++;
	if ((new_env = (char **)malloc(sizeof(char *) * len)) == NULL)
	{
		ft_printf("minishell: cannot allocate memory.\n");
		exit(-1);
	}
	i = 0;
	n = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], search, search_len) != 0)
		{
			new_env[n] = ft_strdup(env[i]);
			n++;
		}
		i++;
	}
	new_env[len - 1] = NULL;
	ft_strdel(&search);
	if (input[1] == NULL)
	{
		ft_print_env(new_env);
		i = 0;
		while (new_env[i])
			ft_strdel(new_env + i++);
		free(new_env);
		new_env = NULL;
	}
	return (new_env);
}

static void	ft_find_and_exec_bin(char mode, char **input, char ***env)
{
	int		n;
	int		i;
	char	**new_env;

	new_env = *env;
	if (mode == 'i' || mode == 'u')
	{
		ft_strdel(input);
		ft_strdel(input + 1);
		input += 2;
		new_env = (mode == 'i') ? NULL : ft_new_env(input, *env);
		ft_strdel(input);
		input++;
	}
	if (input[0])
	{
		if (execve(input[0], input, new_env) == -1
				&& (i = ft_get_in_env("PATH=", *env)) != -1)
			ft_exec_search_in_path(i, input, *env, new_env);
		n = 0;
		ft_printf("minishell: command not found:");
		while (input[n])
			ft_printf(" %s", input[n++]);
		ft_putchar('\n');
	}
	n = 0;
	while (input[n])
		ft_strdel(input + n++);
	exit(-1);
}

int			main(int ac, char **av, char **env)
{
	pid_t	pid;
	char	**input;
	int		i;
	char	mode;

	(void)ac;
	(void)av;
	pid = -1;
	while (42)
	{
		mode = 0;
		ft_printf("$> ");
		if ((input = ft_get_user_input(&mode, &env)) != NULL)
			pid = fork();
		if (pid == 0)
			ft_find_and_exec_bin(mode, input, &env);
		else if (pid > 0)
			wait(NULL);
		if (input != NULL && (i = 0) == 0)
		{
			while (input[i])
				ft_strdel(input + i++);
			free((void *)input);
			input = NULL;
		}
	}
	return (0);
}
