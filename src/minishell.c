/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 17:37:30 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/31 15:06:06 by ebouther         ###   ########.fr       */
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

static int	ft_open_home_dir(char **env)
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
		while ((*env)[i])
		{
			if (i != pos)
			{
				new_env[i] = ft_strdup((*env)[i]);
				if (*modified == 1)
					ft_strdel(*env + i);
			}
			i++;	
		}
		if (*modified == 1)
			free((void *)(*env));
		new_env[len] = NULL;
		*env = new_env;
		*modified = 1;
	}
}

static void	ft_modify_env(char **arg, char ***env, int mode)
{
	static int	modified = 0;

	if (mode == 1)
		ft_setenv(arg, env, &modified);
	else
		ft_unset_env(arg, env, &modified);
}

static void	ft_open_dir(char *dir, char ***env)
{
	char	**arg;
	int		i;
	char	cwd[1024];

	i = 0;
	arg = NULL;
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

static void	ft_change_directory(char **arg, char ***env)
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

static void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
}

static char	**ft_get_user_input(char ***env)
{
	char	**arg;
	char	*str;
	int		len;
	int		i;

	arg = NULL;
	if (get_next_line(1, &str) && ft_strcmp(str, "") != 0)
	{
		if ((arg = ft_strsplit(str, ' ')) != NULL)
		{
			
				len = 0;
				while (arg[len])
					len++;

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
					ft_modify_env(arg, env, 1);
				else if (len == 1)
					ft_print_env(*env);
			}
			else if (ft_strcmp(arg[0], "env") == 0)
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
			{
				ft_strdel(&str);
				return (arg);
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

static void	ft_find_and_exec_bin(char **input, char ***env)
{
	char	*path;
	char	**split;
	int		i;
	int		n;

	if (execve(input[0], input, *env) == -1
			&& (i = ft_get_in_env("PATH=", *env)) != -1)
	{
		split = ft_strsplit((*env)[i], ':');
		i = 0;
		while (split[i] != '\0')
		{
			if (access(path = ft_strjoin_free(ft_strdup(split[i]),
							ft_strjoin_free(ft_strdup("/"),
								ft_strdup(input[0]))), X_OK) == 0)
			{
				if (execve(path, input, *env) == -1)
					ft_printf("minishell: execve: cannot be executed.\n");
				ft_strdel(&path);
				return ;
			}
			ft_strdel(&path);
			i++;
		}

		if (split != NULL)
		{
			n = 0;
			while (split[n])
				ft_strdel(split + n++);
		}
	}
	n = 0;
	ft_printf("minishell: command not found:");
	while (input[n])
		ft_printf(" %s", input[n++]);
	ft_putchar('\n');

	n = 0;
	while (input[n])
		ft_strdel(input + n++);
	exit(-1);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid = -1;
	char	**input;
	int		i;

	(void)ac;
	(void)av;

	while (42)
	{
		ft_printf("$> ");
		if ((input = ft_get_user_input(&env)) != NULL)
			pid = fork();
		if (pid == 0)
			ft_find_and_exec_bin(input, &env);
		else if (pid > 0)
			wait(NULL);
		i = 0;
		if (input != NULL)
		{
			while (input[i])
				ft_strdel(input + i++);
			free((void *)input);
			input = NULL;
		}
	}
	return (0);
}
