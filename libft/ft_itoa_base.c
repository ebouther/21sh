/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:52:28 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/06 19:37:39 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	digit_to_char(int digit)
{
	if (digit < 10)
		return ('0' + digit);
	else
		return ('a' - 10 + digit);
}

static void	ft_inc_val(int *value2, int base, int *length)
{
	while (*value2 >= base)
	{
		*value2 /= base;
		(*length)++;
	}
}

char		*ft_itoa_base(int value, int base)
{
	int		negative;
	char	*str;
	int		length;
	int		value2;

	if (value == -2147483648)
		return ("-2147483648");
	negative = value < 0 && base == 10;
	value = value < 0 ? value * -1 : value;
	length = 1;
	value2 = value;
	ft_inc_val(&value2, base, &length);
	if ((str = (char*)malloc(sizeof(char)
			* ((length += negative) + 1))) == NULL)
		return (NULL);
	str[0] = '-';
	str[length] = '\0';
	while (length-- > negative)
	{
		str[length] = digit_to_char(value % base);
		value /= base;
	}
	return (str);
}
