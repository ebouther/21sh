/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/11 18:07:14 by ebouther          #+#    #+#             */
/*   Updated: 2015/11/26 10:55:32 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if ((unsigned char)*s1++ != (unsigned char)*s2++)
			return ((unsigned char)*(s1 - 1) - (unsigned char)*(s2 - 1));
		else if (*((unsigned char *)(s1 - 1)) == '\0')
			return (0);
	}
	return (0);
}
