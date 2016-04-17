/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/11 18:07:36 by ebouther          #+#    #+#             */
/*   Updated: 2015/11/29 18:02:56 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		n;
	int		first_occur;

	i = 0;
	first_occur = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		n = 0;
		if (needle[n] == haystack[i])
			first_occur = i;
		while (needle[n] == haystack[i + n])
		{
			if (!needle[n + 1])
				return ((char *)(haystack + first_occur));
			n++;
		}
		i++;
	}
	return (NULL);
}
