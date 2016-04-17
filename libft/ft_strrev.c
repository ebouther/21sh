/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:26:28 by ebouther          #+#    #+#             */
/*   Updated: 2015/11/24 15:20:52 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*rev;
	int		i;

	i = 0;
	rev = ft_strnew(ft_strlen(str));
	if (rev)
	{
		rev = ft_strcpy(rev, ft_strswap(str));
		return (rev);
	}
	return (NULL);
}
