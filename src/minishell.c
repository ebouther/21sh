/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 17:37:30 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/18 22:17:49 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_search_in_path(int i, char **input, char **env,
		char **execve_env)
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
	t_new_env n;

	n = (t_new_env){.len = 0, .n = 0, .i = -1, .new_env = NULL, .search = NULL};
	n.search_len = ft_strlen(
			(n.search = ft_strjoin_free(ft_strdup(input[0]),
		ft_strdup("="))));
	while (env[n.len])
		n.len++;
	if ((n.new_env = (char **)malloc(sizeof(char *) * n.len)) == NULL)
		ft_error_exit("minishell: cannot allocate memory.\n");
	while (env[++n.i])
		if (ft_strncmp(env[n.i], n.search, n.search_len) != 0)
			n.new_env[n.n++] = ft_strdup(env[n.i]);
	n.new_env[n.len - 1] = NULL;
	ft_strdel(&n.search);
	if (input[1] == NULL)
	{
		ft_print_env(n.new_env);
		n.i = 0;
		while (n.new_env[n.i])
			ft_strdel(n.new_env + n.i++);
		ft_memdel((void **)&n.new_env);
	}
	return (n.new_env);
}

static void	ft_exec_with_modified_env(char mode, char ***input,
										char ***env, char ***new_env)
{
	if (mode == 'i' || mode == 'u')
	{
		ft_strdel(*input);
		ft_strdel(*input + 1);
		(*input) += 2;
		*new_env = (mode == 'i') ? NULL : ft_new_env(*input, *env);
		if (mode == 'u')
		{
			ft_strdel(*input);
			(*input)++;
		}
	}
}

void		ft_find_and_exec_bin(char mode, char **input, char ***env)
{
	int		n;
	int		i;
	char	**new_env;

	new_env = *env;
	ft_exec_with_modified_env(mode, &input, env, &new_env);
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
	t_main	m;

	(void)ac;
	(void)av;
	m.pid = -1;
	while (42)
	{
		m.mode = 0;
		ft_printf("$> ");
		if ((m.input = ft_get_user_input(&m.mode, &env)) != NULL)
			m.pid = fork();
		if (m.pid == 0)
		{
			//ft_parse_args_for_redirections(); // (higher precedence than pipes)
			if (ft_parse_args_for_pipe(m.mode, &m.input, &env) != 1)
				ft_find_and_exec_bin(m.mode, m.input, &env);
		}
		else if (m.pid > 0)
			wait(NULL);
		if (m.input != NULL && (m.i = 0) == 0)
		{
			while (m.input[m.i])
				ft_strdel(m.input + m.i++);
			free((void *)m.input);
			m.input = NULL;
		}
	}
	return (0);
}
