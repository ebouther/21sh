/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/11 18:07:31 by ebouther          #+#    #+#             */
/*   Updated: 2015/11/23 14:42:32 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		pos;

	i = 0;
	pos = -1;
	if (c == '\0')
		return (ft_strchr(s, c));
	while (s[i])
	{
		if (s[i] == c)
			pos = i;
		i++;
	}
	if (pos == -1)
		return (NULL);
	return ((char *)s + pos);
}
