/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/11 18:06:36 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/02 12:18:38 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;

	if (s == NULL ||
		(cpy = (char *)malloc(sizeof(*cpy) * (ft_strlen(s) + 1))) == NULL)
		return (NULL);
	return (ft_strcpy(cpy, s));
}
