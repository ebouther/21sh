/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 17:39:13 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/06 17:50:01 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_padding_ret_di_core_1(t_conv *conv, char **ret)
{
	int	i;

	i = 0;
	if (ft_strchr(conv->flag, '0') == NULL)
		*ret = ft_strjoin_free(ft_strdup(" "), *ret);
	else
		*ret = ft_strjoin_free(ft_strdup("0"), *ret);
	ft_do_padding(ret, conv, (int)(ft_atoi(conv->padding)
				- ft_strlen(*ret)));
	while ((*ret)[i] == ' ')
		i++;
	if (i - 1 >= 0)
		(*ret)[i - 1] = '+';
	else
		**ret = '+';
}

void	ft_padding_ret_di_core(t_conv *conv, char **ret)
{
	if (ft_strchr(*ret, '-') == NULL)
	{
		if (ft_strcmp(*ret, "0") != 0)
			ft_padding_ret_di_core_1(conv, ret);
		else
		{
			ft_do_padding(ret, conv, (int)(ft_atoi(conv->padding)
						- ft_strlen(*ret)));
			if (**ret != '0' || ft_strchr(conv->flag, '0') != NULL)
				**ret = '+';
			else if (ft_strlen(conv->flag) == 1
					&& ft_strchr(conv->flag, '+') != NULL
					&& conv->padding_pos == -1)
				*ret = ft_strjoin_free(ft_strdup("+"), *ret);
		}
	}
	else
		ft_do_padding(ret, conv, (int)(ft_atoi(conv->padding)
					- ft_strlen(*ret)));
}

void	ft_padding_ret_di_1(t_conv *conv, char **ret)
{
	char	*tmp;

	tmp = NULL;
	if (ft_atoi(*ret) < 0)
	{
		ft_do_padding(ret, conv, (int)(ft_atoi(conv->padding)
					- ft_strlen(*ret)));
		while (ft_strchr(conv->flag, '0') != NULL
				&& ft_strlen(conv->flag) == 1
				&& (tmp = ft_strchr(*ret, ' ')) != NULL)
			*tmp = '0';
	}
	else
	{
		if (ft_strcmp(conv->flag, " 0") == 0
				|| ft_strcmp(conv->flag, "0 ") == 0)
			*ret = ft_strjoin_free(ft_strdup(" "), *ret);
		else
			ft_do_padding(ret, conv, (int)(ft_atoi(conv->padding)
						- ft_strlen(*ret)));
	}
	ft_strdel(&tmp);
}

void	ft_padding_ret_di(t_conv *conv, char **ret, t_env *e)
{
	if (ft_strchr("di", conv->conversion) && ft_strcmp(conv->flag, " 0") == 0
			&& ft_strcmp(*ret, "0") == 0)
	{
		ft_do_padding(ret, conv, (int)(ft_atoi(conv->padding)
					- ft_strlen(*ret)));
		**ret = ' ';
	}
	else if (ft_strchr("di", conv->conversion)
			&& ft_strchr(conv->flag, '+') != NULL)
		ft_padding_ret_di_core(conv, ret);
	else if (ft_strchr("di", conv->conversion)
			&& ft_strchr(conv->flag, ' ') != NULL
			&& conv->conversion_pos == 1
			&& conv->flag_pos == 0 && ft_atoi(*ret) > 0)
		*ret = ft_strjoin_free(ft_strdup(" "), *ret);
	else
		ft_padding_ret_di_1(conv, ret);
	e->offset = conv->conversion_pos + 2;
}

void	ft_padding_ret(t_conv *conv, char **ret, t_env *e)
{
	char	*tmp;

	tmp = NULL;
	if (conv->precision_pos != -1 && ft_strchr("p", conv->conversion) != NULL
			&& *ret != NULL && ft_strcmp(conv->flag, "") == 0)
	{
		if (ft_atoi(conv->padding) > ft_atoi(conv->precision))
		{
			while (((int)ft_strlen(*ret) - 2) < ft_atoi(conv->precision))
				*ret = ft_strjoin_free(*ret, ft_strdup("0"));
		}
		else if (ft_strncmp(*ret, "0x", 2) == 0)
		{
			tmp = *ret;
			*ret = ft_strdup(*ret + 2);
			ft_strdel(&tmp);
			while (((int)ft_strlen(*ret) - 2) < ft_atoi(conv->precision))
				*ret = ft_strjoin_free(ft_strdup("0"), *ret);
			(*ret)[0] = '0';
			(*ret)[1] = 'x';
		}
	}
	ft_padding_ret_di(conv, ret, e);
}
