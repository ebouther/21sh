/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 10:35:41 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/05 10:49:14 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_c(t_conv *conv, t_env *e)
{
	char	*buf;
	char	*ret;

	buf = NULL;
	ret = NULL;
	if (ft_strcmp(conv->modifier, "l") == 0)
	{
		buf = ft_strnew(4);
		ft_utf8_encode(buf, (wchar_t)va_arg(*(e->ap), wchar_t));
		if (*buf == '\0')
			ret = ft_strdup(C_0);
		else
			ret = ft_strdup(buf);
		ft_strdel(&buf);
	}
	else
		ret = ft_char_to_str((char)va_arg(*(e->ap), int));
	return (ret);
}

char	*ft_conv_uc_c(t_env *e)
{
	char	*buf;
	char	*ret;

	buf = NULL;
	ret = NULL;
	buf = ft_strnew(4);
	ft_utf8_encode(buf, (wchar_t)va_arg(*(e->ap), wchar_t));
	if (*buf == '\0')
		ret = ft_strdup(C_0);
	else
		ret = ft_strdup(buf);
	ft_strdel(&buf);
	return (ret);
}

char	*ft_conv_uc_s(t_env *e)
{
	char	*buf;
	char	*ret;
	int		i;
	wchar_t	*wstr;

	i = 0;
	ret = ft_strnew(0);
	buf = ft_strnew(4);
	if ((wstr = (wchar_t *)va_arg(*(e->ap), wchar_t *)) == NULL)
		ret = ft_strdup("(null)");
	else
	{
		while (wstr[i])
		{
			if (ft_utf8_encode(buf, wstr[i]))
				ret = ft_strjoin_free(ret, (wstr[i] == '\0') ?
						ft_strdup(C_0) : ft_char_to_str(wstr[i]));
			else
				ret = ft_strjoin_free(ret, (((*buf) == '\0') ?
							ft_strdup(C_0) : ft_strdup(buf)));
			i++;
		}
	}
	ft_strdel(&buf);
	return (ret);
}

char	*ft_conv_s(t_conv *conv, t_env *e)
{
	char	*ret;

	ret = NULL;
	if (ft_strcmp(conv->modifier, "l") == 0)
		ret = ft_conv_uc_s(e);
	else
	{
		if ((ret = ft_strdup((char *)va_arg(*(e->ap), char *))) == NULL)
		{
			ft_memdel((void **)&ret);
			ret = ft_strdup("(null)");
		}
	}
	return (ret);
}

char	*ft_conv_di(t_conv *conv, t_env *e)
{
	char	*ret;

	ret = NULL;
	if (ft_strcmp(conv->modifier, "l") == 0)
		ret = ft_lltoa_base((long long)va_arg(*(e->ap), long int),
				BASE_10);
	else if (ft_strcmp(conv->modifier, "ll") == 0)
		ret = ft_lltoa_base((long long)va_arg(*(e->ap), long long int),
				BASE_10);
	else if (ft_strcmp(conv->modifier, "h") == 0)
		ret = ft_lltoa_base((short int)va_arg(*(e->ap), int), BASE_10);
	else if (ft_strcmp(conv->modifier, "hh") == 0)
		ret = ft_lltoa_base((signed char)va_arg(*(e->ap), int), BASE_10);
	else if (ft_strcmp(conv->modifier, "j") == 0)
		ret = ft_lltoa_base((intmax_t)va_arg(*(e->ap), unsigned long long),
				BASE_10);
	else if (ft_strcmp(conv->modifier, "z") == 0)
		ret = ft_lltoa_base((size_t)va_arg(*(e->ap), unsigned long long),
				BASE_10);
	else
		ret = ft_itoa((int)va_arg(*(e->ap), int));
	return (ret);
}
