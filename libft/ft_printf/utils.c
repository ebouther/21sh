/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 20:05:07 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/19 19:53:07 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_char_to_str(char c)
{
	char	*ret;

	if (c != 0)
	{
		ret = ft_strnew(1);
		*ret = c;
	}
	else
		ret = ft_strdup(C_0);
	return (ret);
}

int		ft_putstr_0(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (ft_strncmp((const char *)(str + i), C_0, 16) == 0)
		{
			ret++;
			ft_putchar('\0');
			i += 15;
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	return (ret);
}
