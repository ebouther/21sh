/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/11 18:10:49 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/19 19:53:25 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define C_0 "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
# define HEXA_MIN "0123456789abcdef"
# define HEXA_MAJ "0123456789ABCDEF"
# define OCT "01234567"
# define BASE_10 "0123456789"

typedef struct	s_env
{
	int			offset;
	char		*str;
	va_list		*ap;
	char		*res;
	char		*ret;
	char		*tmp;
	int			len_add;
}				t_env;

typedef struct	s_padding
{
	char		**ret;
	char		**padding;
	int			*i;
	int			*len;
}				t_padding;

typedef struct	s_conv
{
	char		*modifier;
	char		conversion;
	int			conversion_pos;
	char		*flag;
	int			flag_pos;
	char		*precision;
	int			precision_pos;
	char		*padding;
	int			padding_pos;
}				t_conv;

int				ft_printf(char const *format, ...);
void			ft_init_conv(t_conv *conv);

/*
** utils.c
*/
char			*ft_char_to_str(char c);
int				ft_putstr_0(char *str);

/*
** conversion.c
*/
char			*ft_get_conversion(char *str, t_conv *conv, t_env *e);
char			*ft_conv_c(t_conv *conv, t_env *e);
char			*ft_conv_uc_c(t_env *e);
char			*ft_conv_uc_s(t_env *e);
char			*ft_conv_s(t_conv *conv, t_env *e);
char			*ft_conv_di(t_conv *conv, t_env *e);
char			*ft_conv_u(t_conv *conv, t_env *e);
char			*ft_conv_x(t_conv *conv, t_env *e);
char			*ft_conv_uc_x(t_conv *conv, t_env *e);
char			*ft_conv_p(t_conv *conv, t_env *e);
char			*ft_conv_o(t_conv *conv, t_env *e);

/*
** precision.c
*/
char			*ft_get_precision(char *str, t_conv *conv, t_env *e);

/*
** flags.c
*/
char			*ft_get_flags(char *str, t_conv *conv, t_env *e);

/*
** padding.c
*/
char			*ft_get_padding(char *str, t_env *e);
void			ft_do_padding(char **ret, t_conv *conv, int len);
void			ft_do_padding_switch(t_conv *conv, char **ret,
					int len, int offset);
void			ft_do_padding_switch_2(t_conv *conv, char **ret,
					int offset, char *padding);
void			ft_do_padding_switch_2_1(t_conv *conv, char **ret,
					char *padding, int i);
void			ft_padding_ret(t_conv *conv, char **ret, t_env *e);
void			ft_padding_ret_di(t_conv *conv, char **ret, t_env *e);
void			ft_padding_ret_di_1(t_conv *conv, char **ret);
void			ft_padding_ret_di_core(t_conv *conv, char **ret);
void			ft_padding_ret_di_core_1(t_conv *conv, char **ret);
void			ft_store_padding(char *str, t_conv *conv);
void			ft_store_padding_core(char *str, t_conv *conv, int *i, int *n);
char			*ft_padding_ret_null(char *str, t_conv *conv, t_env *e);
void			ft_do_padding_switch_3(t_conv *conv, char **ret,
					int offset, char *padding);
void			ft_do_padding_switch_3_1(t_conv *conv, char **ret,
					char **padding);
void			ft_do_padding_switch_3_2(t_conv *conv, char **ret,
					char **padding, int i);
void			ft_do_padding_switch_4(t_conv *conv, char **ret,
					int offset, char *padding);
void			ft_do_padding_switch_5(t_conv *conv, char **ret,
					int offset, char *padding);
void			ft_do_padding_switch_5_1(char **ret,
					int offset, char *padding);
void			ft_padding_switch(t_padding *p, t_conv *conv, int *offset);
void			ft_padding_switch_core(t_padding *p, t_conv *conv, int *offset);

#endif
