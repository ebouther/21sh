/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 10:08:31 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/06 15:52:45 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_get_pos(char *str, t_conv *conv)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("sSpdDioOuUxXcC%", str[i]) != NULL)
		{
			conv->conversion = str[i];
			conv->conversion_pos = i;
			break ;
		}
		else if (ft_strchr("hljz .1234567890 #0-+", str[i]) == NULL)
			break ;
		i++;
	}
}

static void	ft_get_modifier(char *str, t_conv *conv)
{
	int	i;

	i = 0;
	if (conv->conversion_pos >= 1)
	{
		i = 0;
		while (i <= conv->conversion_pos)
		{
			if (str[(conv->conversion_pos - 2) + i] == 'h' ||
					str[(conv->conversion_pos - 2) + i] == 'l' ||
					str[(conv->conversion_pos - 2) + i] == 'j' ||
					str[(conv->conversion_pos - 2) + i] == 'z')
				conv->modifier = ft_strjoin_free(conv->modifier,
						ft_char_to_str(str[(conv->conversion_pos - 2) + i]));
			i++;
		}
	}
}

static char	*ft_conv_switch_2(t_conv *conv, t_env *e)
{
	char	*ret;

	ret = NULL;
	if (conv->conversion == 'U')
		ret = ft_llntoa_base((unsigned long long)va_arg(*(e->ap),
					unsigned long long), BASE_10);
	else if (conv->conversion == 'x')
		ret = ft_conv_x(conv, e);
	else if (conv->conversion == 'X')
		ret = ft_conv_uc_x(conv, e);
	else if (conv->conversion == 'p')
		ret = ft_conv_p(conv, e);
	else if (conv->conversion == '%')
		ret = ft_strdup("%");
	else if (conv->conversion == 'D')
		ret = ft_lltoa_base((long long)va_arg(*(e->ap), long), BASE_10);
	else if (conv->conversion == 'o')
		ret = ft_conv_o(conv, e);
	else if (conv->conversion == 'O')
		ret = ft_llntoa_base((unsigned long)va_arg(*(e->ap), unsigned long),
				(char *)"01234567");
	return (ret);
}

static char	*ft_conv_switch(t_conv *conv, t_env *e)
{
	char	*ret;
	char	*buf;

	ret = NULL;
	buf = NULL;
	if (conv->conversion == 'c')
		ret = ft_conv_c(conv, e);
	else if (conv->conversion == 'C')
		ret = ft_conv_uc_c(e);
	else if (conv->conversion == 's')
		ret = ft_conv_s(conv, e);
	else if (conv->conversion == 'S')
		ret = ft_conv_uc_s(e);
	else if (conv->conversion == 'd' || conv->conversion == 'i')
		ret = ft_conv_di(conv, e);
	else if (conv->conversion == 'u')
		ret = ft_conv_u(conv, e);
	else
		ret = ft_conv_switch_2(conv, e);
	return (ret);
}

char		*ft_get_conversion(char *str, t_conv *conv, t_env *e)
{
	if (ft_strchr("hljz sSpdDioOuUxXcC% .1234567890 #0-+", str[0]) == NULL)
		return (ft_strnew(0));
	ft_get_pos(str, conv);
	if (conv->conversion == 0)
		return (NULL);
	ft_get_modifier(str, conv);
	return (ft_conv_switch(conv, e));
}
