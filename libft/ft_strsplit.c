/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 18:43:50 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/06 19:40:50 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_number(char const *s, char c)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		result++;
		if (s[i - 1] == c)
			result -= 1;
	}
	return (result);
}

static int	words_size(char const *s, char c, int i)
{
	int		res;

	res = 0;
	while (s[i] != c && s[i] != '\0')
	{
		res++;
		i++;
	}
	return (res);
}

static char	**new_tab(char const *s, char c, int result)
{
	char	**str;
	int		i;
	int		j;
	int		word_size;

	i = 0;
	j = 0;
	if (!(str = (char**)malloc(sizeof(char*) * result + 1)))
		return (NULL);
	while (i < result)
	{
		word_size = 0;
		while (s[j] == c && s[j] != '\0')
			j++;
		word_size = words_size(s, c, j);
		while (s[j] != c && s[j] != '\0')
			j++;
		if ((str[i] = (char*)malloc(sizeof(char) * (word_size + 1))) == NULL)
			return (NULL);
		i++;
	}
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!s || !(str = new_tab(s, c, words_number(s, c))))
		return (NULL);
	while (i < words_number(s, c))
	{
		j = 0;
		while (s[k] == c && s[k] != '\0')
			k++;
		while (s[k] != c && s[k] != '\0')
		{
			str[i][j] = s[k];
			j++;
			k++;
		}
		str[i++][j] = '\0';
	}
	str[i] = NULL;
	return (str);
}
