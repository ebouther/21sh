/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 10:36:25 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/05 10:50:07 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_u(t_conv *conv, t_env *e)
{
	char	*ret;

	ret = NULL;
	if (ft_strcmp(conv->modifier, "l") == 0)
		ret = ft_llntoa_base((long long)va_arg(*(e->ap), unsigned long),
				BASE_10);
	else if (ft_strcmp(conv->modifier, "ll") == 0 || ft_strcmp(conv->modifier,
				"j") == 0 || ft_strcmp(conv->modifier, "z") == 0)
		ret = ft_llntoa_base((long long)va_arg(*(e->ap), unsigned long long),
				BASE_10);
	else if (ft_strcmp(conv->modifier, "h") == 0)
		ret = ft_llntoa_base((unsigned short)va_arg(*(e->ap), unsigned int),
				BASE_10);
	else if (ft_strcmp(conv->modifier, "hh") == 0)
		ret = ft_llntoa_base((unsigned char)va_arg(*(e->ap), unsigned int),
				BASE_10);
	else
		ret = ft_llntoa_base((unsigned int)va_arg(*(e->ap),
					unsigned int), BASE_10);
	return (ret);
}

char	*ft_conv_x(t_conv *conv, t_env *e)
{
	char	*ret;

	ret = NULL;
	if (ft_strcmp(conv->modifier, "l") == 0)
		ret = ft_llntoa_base((long long)va_arg(*(e->ap), unsigned long),
				HEXA_MIN);
	else if (ft_strcmp(conv->modifier, "ll") == 0 || ft_strcmp(conv->modifier,
				"j") == 0 || ft_strcmp(conv->modifier, "z") == 0)
		ret = ft_llntoa_base((long long)va_arg(*(e->ap), unsigned long long),
				HEXA_MIN);
	else if (ft_strcmp(conv->modifier, "h") == 0)
		ret = ft_llntoa_base((unsigned short)va_arg(*(e->ap), unsigned int),
				HEXA_MIN);
	else if (ft_strcmp(conv->modifier, "hh") == 0)
		ret = ft_llntoa_base((unsigned char)va_arg(*(e->ap), unsigned int),
				HEXA_MIN);
	else
		ret = ft_llntoa_base((unsigned int)va_arg(*(e->ap),
					unsigned int), HEXA_MIN);
	return (ret);
}

char	*ft_conv_uc_x(t_conv *conv, t_env *e)
{
	char	*ret;

	ret = NULL;
	if (ft_strcmp(conv->modifier, "l") == 0)
		ret = ft_llntoa_base((long long)va_arg(*(e->ap), unsigned long),
				HEXA_MAJ);
	else if (ft_strcmp(conv->modifier, "ll") == 0 || ft_strcmp(conv->modifier,
				"j") == 0
			|| ft_strcmp(conv->modifier, "z") == 0)
		ret = ft_llntoa_base((long long)va_arg(*(e->ap), unsigned long long),
				HEXA_MAJ);
	else if (ft_strcmp(conv->modifier, "h") == 0)
		ret = ft_llntoa_base((unsigned short)va_arg(*(e->ap), unsigned int),
				HEXA_MAJ);
	else if (ft_strcmp(conv->modifier, "hh") == 0)
		ret = ft_llntoa_base((unsigned char)va_arg(*(e->ap), unsigned int),
				HEXA_MAJ);
	else
		ret = ft_llntoa_base((unsigned int)va_arg(*(e->ap),
					unsigned int), HEXA_MAJ);
	return (ret);
}

char	*ft_conv_p(t_conv *conv, t_env *e)
{
	char	*ret;

	ret = NULL;
	if ((ret = ft_llntoa_base((unsigned long)va_arg(*(e->ap), void *),
					(char *)HEXA_MIN)) == NULL)
	{
		ft_memdel((void **)&ret);
		ret = ft_strdup("(null)");
	}
	else
	{
		if (conv->precision_pos != -1 && ft_strcmp(ret, "0") == 0)
		{
			ft_strdel(&ret);
			ret = ft_strnew(0);
		}
		ret = ft_strjoin_free(ft_strdup("0x"), ret);
	}
	return (ret);
}

char	*ft_conv_o(t_conv *conv, t_env *e)
{
	char	*ret;

	ret = NULL;
	if (ft_strcmp(conv->modifier, "l") == 0)
		ret = ft_llntoa_base((long long)va_arg(*(e->ap), unsigned long),
			OCT);
	else if (ft_strcmp(conv->modifier, "ll") == 0 || ft_strcmp(conv->modifier,
			"j") == 0 || ft_strcmp(conv->modifier, "z") == 0)
		ret = ft_llntoa_base((long long)va_arg(*(e->ap), unsigned long long),
				OCT);
	else if (ft_strcmp(conv->modifier, "h") == 0)
		ret = ft_llntoa_base((unsigned short)va_arg(*(e->ap), unsigned int),
				OCT);
	else if (ft_strcmp(conv->modifier, "hh") == 0)
		ret = ft_llntoa_base((unsigned char)va_arg(*(e->ap), unsigned int),
				OCT);
	else
		ret = ft_llntoa_base((unsigned int)va_arg(*(e->ap), unsigned int),
				(char *)OCT);
	return (ret);
}
