/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/11 18:05:03 by ebouther          #+#    #+#             */
/*   Updated: 2015/11/24 14:08:16 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n--)
	{
		*((unsigned char *)dest) = *((unsigned char *)src);
		dest++;
		if (*((unsigned char *)src) == (unsigned char)c)
			return (dest);
		src++;
	}
	return (NULL);
}
