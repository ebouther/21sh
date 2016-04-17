/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 10:58:52 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/06 18:53:56 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_do_precision_2(char **ret, int *i)
{
	if (*i > 0)
		*ret = ft_strjoin_free(ft_strdup("0"), *ret);
	else
	{
		(*i)--;
		if (*i == -1 && **ret == '-')
			**ret = '0';
		else
			*ret = ft_strjoin_free(ft_strdup("0"), *ret);
	}
}

static void	ft_do_precision_1(char **ret, t_conv *conv)
{
	int	i;

	i = 0;
	if (ft_atoi(*ret) >= 0)
		i = 1;
	if (ft_atoi(conv->precision) == 0 && ft_strcmp(*ret, "0") == 0)
	{
		ft_strdel(ret);
		*ret = ft_strnew(0);
	}
	else
	{
		while ((int)ft_strlen(*ret) < ft_atoi(conv->precision))
			ft_do_precision_2(ret, &i);
		if (i < 0)
			*ret = ft_strjoin_free(ft_strdup("-"), *ret);
	}
}

static void	ft_do_precision_s(char **ret, t_conv *conv)
{
	int		i;
	int		n;
	char	*tmp;

	i = 0;
	n = 0;
	tmp = NULL;
	while ((*ret)[i] && i < ft_atoi(conv->precision))
	{
		if ((*ret)[i] >= 0x0000 && (*ret)[i] <= 0x007F)
		{
			n = 0;
			i++;
		}
		else
		{
			i += 3;
			n = 1;
		}
	}
	if (i > ft_atoi(conv->precision) && n == 1)
		i -= 3;
	*ret = ft_strncat(ft_strnew(ft_atoi(conv->precision)),
			tmp = *ret, i);
	ft_strdel(&tmp);
}

static void	ft_do_precision(char **ret, t_conv *conv)
{
	if (conv->precision_pos != -1
			&& ft_strchr("sS", conv->conversion) && *ret != NULL)
	{
		if (ft_atoi(conv->precision) < (int)ft_strlen(*ret))
			ft_do_precision_s(ret, conv);
	}
	if (conv->precision_pos != -1 && ft_strchr("dioOuxX", conv->conversion)
			&& *ret != NULL)
		ft_do_precision_1(ret, conv);
}

char		*ft_get_precision(char *str, t_conv *conv, t_env *e)
{
	char	*ret;
	int		i;
	int		n;

	i = 0;
	conv->precision = ft_strnew(0);
	while (str[i] && str[i] != '%'
		&& ft_strchr("hljz sSpdDioOuUxXcC% .1234567890 #0-+", str[i]) != NULL)
	{
		if (str[i] == '.')
		{
			n = 1;
			conv->precision_pos = i;
			while (ft_isdigit(str[i + n]) == 1)
			{
				conv->precision = ft_strjoin_free(conv->precision,
						ft_char_to_str(str[i + n++]));
			}
			break ;
		}
		i++;
	}
	ret = ft_get_conversion(str, conv, e);
	ft_do_precision(&ret, conv);
	return (ret);
}
