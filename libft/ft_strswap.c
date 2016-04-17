/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:48:36 by ebouther          #+#    #+#             */
/*   Updated: 2015/11/24 16:21:59 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strswap(char *str)
{
	char	tmp;
	int		i;
	size_t	len;

	len = ft_strlen(str) - 1;
	i = 0;
	while (i < (int)(len / 2))
	{
		tmp = str[i];
		str[i] = str[len - i];
		str[len - i] = tmp;
		i++;
	}
	return (str);
}
