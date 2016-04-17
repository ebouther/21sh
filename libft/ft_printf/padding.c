/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 09:00:56 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/06 17:48:39 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_do_padding_switch_2_1(t_conv *conv, char **ret,
		char *padding, int i)
{
	if (ft_strchr(conv->flag, '-') == NULL)
	{
		while (padding[i] == ' ')
			i++;
		if (i - 1 >= 0)
		{
			padding[i - 1] = '0';
			*ret = ft_strjoin_free(padding, *ret);
		}
		else
			*ret = ft_strjoin_free(
					padding = ft_strjoin_free(ft_strdup("0"),
						padding), *ret);
	}
	else
	{
		if ((int)ft_strlen(padding) > 1)
		{
			*ret = ft_strjoin(ft_strdup("0"), *ret);
			padding[ft_strlen(padding) - 1] = '\0';
			*ret = ft_strjoin_free(*ret, padding);
		}
	}
}

void	ft_do_padding_switch_2(t_conv *conv, char **ret,
		int offset, char *padding)
{
	char	*tmp2;
	char	*tmp;
	int		i;

	tmp2 = NULL;
	tmp = NULL;
	i = 0;
	if (ft_strchr(conv->flag, '0') != NULL && conv->conversion == 'p')
		*ret = ft_strjoin(
				(tmp2 = *ret),
				tmp = padding);
	else if (ft_strchr(conv->flag, '#') != NULL
			&& ft_strchr("Oo", conv->conversion) != NULL
			&& ft_strcmp(*ret, "0") != 0)
	{
		if (conv->precision_pos != -1 && ft_strlen(conv->precision) > 0
				&& ft_strcmp(conv->precision, "0") != 0)
			*ret = ft_strjoin_free(padding, *ret);
		else
			ft_do_padding_switch_2_1(conv, ret, padding, i);
	}
	else
		ft_do_padding_switch_3(conv, ret, offset, padding);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

void	ft_do_padding_switch(t_conv *conv, char **ret, int len, int offset)
{
	char		*padding;
	int			i;
	t_padding	p;

	i = 0;
	padding = ft_strnew(0);
	p.ret = ret;
	p.padding = &padding;
	p.i = &i;
	p.len = &len;
	if (ft_strcmp(conv->padding, "") != 0)
	{
		while (i < len)
		{
			ft_padding_switch(&p, conv, &offset);
			i++;
		}
	}
	ft_do_padding_switch_2(conv, ret, offset, padding);
}

void	ft_do_padding(char **ret, t_conv *conv, int len)
{
	int		i;
	int		offset;

	i = 0;
	offset = 0;
	while ((*ret)[i])
	{
		if (ft_strncmp((const char *)((*ret) + i), C_0, 16) == 0)
			len += 15;
		i++;
	}
	ft_do_padding_switch(conv, ret, len, offset);
}

char	*ft_get_padding(char *str, t_env *e)
{
	t_conv	conv;
	char	*ret;

	ft_init_conv(&conv);
	ret = ft_get_flags(str, &conv, e);
	ft_store_padding(str, &conv);
	if (ret == NULL)
		ret = ft_padding_ret_null(str, &conv, e);
	else
		ft_padding_ret(&conv, &ret, e);
	ft_strdel(&conv.flag);
	ft_strdel(&conv.padding);
	ft_strdel(&conv.precision);
	ft_strdel(&conv.modifier);
	return (ret);
}
