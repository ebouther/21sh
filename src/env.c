/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 19:28:25 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/13 20:36:08 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				printf("minishell: set $HOME environment \
variable before using ~\n");
		}
		i++;
	}
}
