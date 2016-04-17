/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 21:59:53 by ebouther          #+#    #+#             */
/*   Updated: 2016/01/27 22:04:34 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_ten_pow(int ten, int p)
{
	if (p <= 0)
		return (1);
	else
		return (ft_ten_pow(ten, p - 1) * 10);
}

double			ft_atod(char *s)
{
	int			i;
	int			j;
	double		integer;
	double		deci;

	i = 0;
	deci = 0.0;
	while (s[i] && s[i] != '.')
		i++;
	if (s[i] == '\0')
		return ((double)(ft_atoi(s)));
	else if (s[i] == '.')
	{
		integer = (double)ft_atoi(ft_strsub(s, 0, i));
		deci = (double)ft_atoi(ft_strsub(s, i + 1, ft_strlen(s) - i - 1));
		j = i + 1;
		while (ft_isdigit(s[j]) == 1)
			j++;
		deci = deci / ft_ten_pow(1, j - i - 1);
		deci = deci + integer;
	}
	return (deci);
}
