/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 17:44:14 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/06 17:53:20 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_do_padding_switch_5(t_conv *conv, char **ret,
		int offset, char *padding)
{
	char	*tmp2;
	char	*tmp;

	tmp2 = NULL;
	tmp = NULL;
	if (ft_strchr(conv->flag, '-') != NULL)
		ft_do_padding_switch_5_1(ret, offset, padding);
	else
	{
		if (**ret == '+')
			*ret = ft_strjoin_free(ft_strdup("+"), ft_strjoin(
						tmp = padding,
						(tmp2 = *ret) + offset + 1));
		else
			*ret = ft_strjoin(
					tmp = padding,
					(tmp2 = *ret) + offset);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
}

void	ft_do_padding_switch_4(t_conv *conv, char **ret,
		int offset, char *padding)
{
	if (ft_strchr(conv->flag, '#') != NULL
			&& ft_strchr("X", conv->conversion) != NULL
			&& ft_strcmp(*ret, "0") != 0)
		*ret = ft_strjoin_free(
				padding = ft_strjoin_free(ft_strdup("0X"), padding), *ret);
	else
		ft_do_padding_switch_5(conv, ret, offset, padding);
}

void	ft_do_padding_switch_3_2(t_conv *conv, char **ret,
		char **padding, int i)
{
	if (ft_strchr(conv->flag, '-') == NULL)
	{
		(*padding)[i - 2] = '0';
		(*padding)[i - 1] = 'x';
		*ret = ft_strjoin_free(
				*padding, *ret);
	}
	else
	{
		if ((int)(ft_strlen(*padding) - 2) >= 0)
			(*padding)[ft_strlen(*padding) - 2] = '\0';
		*ret = ft_strjoin_free(ft_strdup("0x"), ft_strjoin_free(
					*ret, *padding));
	}
}

void	ft_do_padding_switch_3_1(t_conv *conv, char **ret, char **padding)
{
	int		i;

	i = 0;
	while ((*padding)[i] == ' ')
		i++;
	if (i - 1 > 0 && i - 2 >= 0)
		ft_do_padding_switch_3_2(conv, ret, padding, i);
	else
	{
		if (conv->padding_pos != -1)
		{
			(*padding)[0] = '0';
			(*padding)[1] = 'x';
			*ret = ft_strjoin_free(
					*padding, *ret);
		}
		else
			*ret = ft_strjoin_free(ft_strdup("0x"), *ret);
	}
}

void	ft_do_padding_switch_3(t_conv *conv, char **ret,
		int offset, char *padding)
{
	if (ft_strchr(conv->flag, '#') != NULL
			&& ft_strchr("x", conv->conversion) != NULL
			&& ft_strcmp(*ret, "0") != 0)
	{
		if (conv->precision_pos != -1 && ft_strcmp(*ret, "") == 0
				&& ft_strcmp(*ret, "0") != 0)
			*ret = ft_strjoin_free(padding, *ret);
		else
			ft_do_padding_switch_3_1(conv, ret, &padding);
	}
	else
		ft_do_padding_switch_4(conv, ret, offset, padding);
}
