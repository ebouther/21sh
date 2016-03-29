/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 17:37:30 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/29 12:13:03 by ebouther         ###   ########.fr       */
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

static char	*ft_get_user_input(void)
{
	char	*str;

	str = NULL;
	if (get_next_line(1, &str))
		return (str);
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	pid_t	father;
	char	*input;
	int		i;
	char	**split;

	(void)ac;
	(void)av;
	father = fork();

	if (father > 0)
	{
		wait(NULL);
		ft_printf("test\n");
	}
	if (father == 0)
	{
		if ((input = ft_get_user_input()) != NULL)
		{
			ft_printf("INPUT: '%s'\n", input);
			if ((i = ft_get_in_env("PATH", env)) != -1)
			{
				//Should open all paths in env and search for input
				ft_printf("FOUND\n");
				split = ft_strsplit(env[i], ':');
				while (*split != '\0')
				{
					ft_printf("SPLIT\n");
					if (ft_strstr(*split, input) != NULL)
					{
						ft_printf("OK\n");
						execve(*split, av, NULL);
					}
					split++;
				}
			}
		}
	}
	return (0);
}
