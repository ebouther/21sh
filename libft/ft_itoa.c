/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/11 18:01:22 by ebouther          #+#    #+#             */
/*   Updated: 2015/11/26 14:36:48 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getlength(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len + 1);
}

static void		ft_fillstr(char *str, int n, size_t len)
{
	int	sign;

	sign = 0;
	if (n < 0)
	{
		n *= -1;
		sign = -1;
	}
	while (len)
	{
		str[-1 + len--] = (n % 10) + '0';
		n /= 10;
	}
	if (sign == -1)
		str[0] = '-';
}

char			*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_getlength(n);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	ft_fillstr(str, n, len);
	return (str);
}
