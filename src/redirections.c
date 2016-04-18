/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 21:13:35 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/18 22:16:25 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pipe(int mode, char **arg1, char **arg2, char ***env)
{
	pid_t child = -1;
	int	pdes[2];

	pipe( pdes );
	child = fork();
	if (child == 0)
	{
		close(pdes[READ_END]);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		ft_find_and_exec_bin(mode, arg1, env);
		//execve(arg1[0], arg1, *env);
	}
	else if (child > 0)
	{
		close(pdes[WRITE_END]);
		dup2(pdes[READ_END], STDIN_FILENO);
		wait(NULL);
		ft_find_and_exec_bin(mode, arg2, env);
	}
	else
	{
		close(pdes[READ_END]);
		close(pdes[WRITE_END]);
		ft_printf("minishell: cannot fork\n");
		exit(-1);
	}
	return (1);
}


int	ft_parse_args_for_pipe(int mode, char ***arg, char ***env)
{
	int	i;

	i = 0;
	while ((*arg)[i])
	{
		if (ft_strcmp((*arg)[i], "|") == 0)
		{
			ft_strdel((*arg) + i);
			(*arg)[i] = NULL;
			if ((*arg)[i + 1] != NULL)
				return (ft_pipe(mode, *arg, (*arg) + i + 1, env));
		}
		i++;
	}
	return (0);
}
