/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 17:45:17 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/06 17:54:33 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_padding_switch_core(t_padding *p, t_conv *conv, int *offset)
{
	if (**(p->ret) == '-' && *(p->i) == 0)
	{
		*(p->padding) = ft_strjoin_free(*(p->padding), ft_strdup("-"));
		*offset = 1;
		(*(p->len))++;
	}
	else if (conv->padding_pos != -1 && conv->precision_pos != -1
			&& ft_strlen(conv->precision) > 0
			&& ft_atoi(conv->padding) > ft_atoi(conv->precision))
		*(p->padding) = ft_strjoin_free(*(p->padding), ft_strdup(" "));
	else
		*(p->padding) = ft_strjoin_free(*(p->padding), ft_strdup("0"));
}

void	ft_padding_switch(t_padding *p, t_conv *conv, int *offset)
{
	if ((ft_strchr("oduixXcsSp%", conv->conversion) != NULL)
			|| (conv->conversion_pos == -1))
	{
		if (ft_strchr(conv->flag, '-') != NULL)
		{
			if (**(p->ret) == '-' && *(p->i) == 0)
			{
				*(p->padding) = ft_strjoin_free(*(p->padding), ft_strdup("-"));
				*offset = 1;
				(*(p->len))++;
			}
			else
				*(p->padding) = ft_strjoin_free(ft_strdup(" "), *(p->padding));
		}
		else if (ft_strchr(conv->flag, '0') != NULL)
			ft_padding_switch_core(p, conv, offset);
		else
			*(p->padding) = ft_strjoin_free(*(p->padding), ft_strdup(" "));
	}
	else
		*(p->padding) = ft_strjoin_free(*(p->padding), ft_strdup(" "));
}

void	ft_do_padding_switch_5_1(char **ret,
		int offset, char *padding)
{
	char	*tmp2;
	char	*tmp;

	tmp2 = NULL;
	tmp = NULL;
	*ret = ft_strjoin(
			(tmp2 = *ret) + offset,
			tmp = padding);
	if ((*ret)[ft_strlen(*ret) - 1] == '-')
	{
		(*ret)[ft_strlen(*ret) - 1] = '\0';
		*ret = ft_strjoin_free(ft_strdup("-"), *ret);
	}
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}
