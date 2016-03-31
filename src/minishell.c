/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 17:37:30 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/31 19:37:20 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
