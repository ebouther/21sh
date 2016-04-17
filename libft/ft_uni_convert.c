/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uni_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 14:05:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/03 16:04:54 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_ascii_code_point(int val)
{
	return (val >= 0x0000 && val <= 0x007F);
}

static int	cut_utf8_1(char *buf, int code)
{
	buf[0] = (char)code;
	return (1);
}

static void	cut_utf8(int *count, int *offset, int mode)
{
	if (mode == 2)
	{
		*count = 1;
		*offset = 0xC0;
	}
	else if (mode == 3)
	{
		*count = 2;
		*offset = 0xE0;
	}
	else
	{
		*count = 3;
		*offset = 0xF0;
	}
}

int			ft_utf8_encode(char *buf, int codepoint)
{
	int		count;
	int		offset;
	int		i;
	int		temp;

	count = 0;
	offset = 0;
	if (is_ascii_code_point(codepoint))
		return (cut_utf8_1(buf, codepoint));
	if (codepoint >= 0x0080 && codepoint <= 0x07FF)
		cut_utf8(&count, &offset, 2);
	else if (codepoint >= 0x0800 && codepoint <= 0xFFFF)
		cut_utf8(&count, &offset, 3);
	else if (codepoint >= 0x10000 && codepoint <= 0x10FFFF)
		cut_utf8(&count, &offset, 4);
	i = 0;
	buf[i] = (codepoint >> (6 * count)) + offset;
	i++;
	count++;
	while (--count > 0)
	{
		temp = codepoint >> (6 * (count - 1));
		buf[i++] = 0x80 | (temp & 0x3f);
	}
	return (0);
}
