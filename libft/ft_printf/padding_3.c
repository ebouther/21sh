/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 17:42:19 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/06 17:50:50 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_padding_ret_null(char *str, t_conv *conv, t_env *e)
{
	char	*ret;

	ret = ft_strnew(0);
	if (conv->flag_pos == -1 && conv->precision_pos == -1
			&& conv->conversion_pos == -1)
	{
		ft_do_padding(&ret, conv,
				(int)(ft_atoi(conv->padding) - ft_strlen(ret)) - 1);
		e->offset = ft_strlen(conv->padding) + 1;
	}
	else if ((ft_strchr(conv->flag, '-') != NULL
				|| ft_strchr(conv->flag, '0') != NULL)
			&& conv->conversion_pos == -1)
	{
		ft_strdel(&ret);
		ret = ft_char_to_str(str[ft_strlen(conv->padding)
				+ ft_strlen(conv->flag) + ((conv->precision_pos != -1
						&& ft_strcmp(conv->precision, "") == 0) ? (1) : (0))]);
		ft_do_padding(&ret, conv, (int)(ft_atoi(conv->padding)
					- ft_strlen(ret)));
		e->offset = ft_strlen(conv->padding) + ft_strlen(conv->flag)
			+ ((conv->precision_pos != -1
			&& ft_strcmp(conv->precision, "") == 0) ? (1) : (0)) + 2;
	}
	return (ret);
}

void	ft_store_padding_core(char *str, t_conv *conv, int *i, int *n)
{
	while ((ft_isdigit(str[*i + *n]) && ((*i + *n) < conv->conversion_pos))
			|| (ft_isdigit(str[*i + *n]) && conv->conversion_pos == -1))
	{
		if (((conv->precision_pos != -1)
					&& ((*i + *n) < conv->precision_pos))
				|| (conv->precision_pos == -1))
		{
			if (conv->padding_pos == -1)
				conv->padding_pos = *i + *n;
			conv->padding = ft_strjoin_free(conv->padding,
					ft_char_to_str(str[*i + *n]));
		}
		(*n)++;
	}
}

void	ft_store_padding(char *str, t_conv *conv)
{
	int		i;
	int		n;

	i = 0;
	while (str[i] && str[i] != '%')
	{
		n = 0;
		if (((str[i + n] > '0' && str[i + n] <= '9')
					&& ((i + n) < conv->conversion_pos))
				|| ((str[i + n] > '0' && str[i + n] <= '9')
					&& conv->conversion_pos == -1))
		{
			ft_store_padding_core(str, conv, &i, &n);
			break ;
		}
		i++;
	}
}
