/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/11 18:05:41 by ebouther          #+#    #+#             */
/*   Updated: 2015/11/29 17:23:13 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void			*s_begin;
	unsigned int	i;

	s_begin = s;
	i = 0;
	if (n == 0)
		return (s);
	while (i < n)
	{
		*((unsigned char *)s) = (unsigned char)c;
		s++;
		i++;
	}
	return (s_begin);
}
