/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:20:29 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/01 20:01:15 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_new_env(char **arg, char ***env, int *modified, char *tmp, int pos, char **new_env)
{
	int		i;

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
}

static void	ft_setenv(char **arg, char ***env, int *modified)
{
	int		len;
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
	ft_new_env(arg, env, modified, tmp, pos, new_env);
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
	int		n;
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
		n = 0;
		while ((*env)[i])
		{
			if (i != pos)
			{
				new_env[n] = ft_strdup((*env)[i]);
				if (*modified == 1)
					ft_strdel(*env + i);
				n++;
			}
			i++;
		}
		if (*modified == 1)
			free((void *)(*env));
		new_env[n] = NULL;
		*env = new_env;
		*modified = 1;
	}
}

void		ft_modify_env(char **arg, char ***env, int mode)
{
	static int	modified = 0;

	if (mode == 1)
		ft_setenv(arg, env, &modified);
	else
		ft_unset_env(arg, env, &modified);
}

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
}
