/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/11 18:09:41 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/06 16:04:41 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_init_conv(t_conv *conv)
{
	conv->modifier = ft_strnew(0);
	conv->conversion = 0;
	conv->conversion_pos = -1;
	conv->precision = NULL;
	conv->precision_pos = -1;
	conv->flag = ft_strnew(0);
	conv->flag_pos = -1;
	conv->padding = ft_strnew(0);
	conv->padding_pos = -1;
}

static void	ft_init_env(char const *s, va_list *ap, t_env *e)
{
	e->str = ft_strdup(s);
	e->ap = ap;
	e->res = ft_strnew(0);
	e->tmp = NULL;
	e->ret = NULL;
	e->offset = 2;
	e->len_add = 0;
}

static void	ft_printf_no_conv(int *len, t_env *e)
{
	int		i;

	i = 0;
	while (i < *len && (e->ret = ft_strchr(e->str + i, '%')) != NULL)
	{
		*(e->ret) = '\0';
		e->res = ft_strjoin_free(e->res, ft_strjoin(e->str + i,
					e->tmp = ft_get_padding(e->ret + 1, e)));
		i += (int)(e->ret - (e->str + i)) + e->offset;
		ft_strdel(&(e->tmp));
	}
	if (i < *len)
	{
		e->res = ft_strjoin(
				e->tmp = e->res, e->str + i);
		ft_strdel(&(e->tmp));
	}
	*len = ft_strlen(e->res);
	*len -= ft_putstr_0(e->res) * 15;
}

int			ft_printf(char const *s, ...)
{
	t_env	env;
	va_list	ap;
	int		len;

	va_start(ap, s);
	ft_init_env(s, &ap, &env);
	len = ft_strlen(s);
	if (ft_strcmp(s, "%") == 0)
	{
		env.res = ft_strdup("");
		len = 0;
	}
	else
		ft_printf_no_conv(&len, &env);
	va_end(*(env.ap));
	ft_strdel(&env.res);
	ft_strdel(&env.str);
	return (len + env.len_add);
}
