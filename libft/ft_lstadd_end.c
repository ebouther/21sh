/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <ebouther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/11 18:03:26 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/06 15:47:07 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (alst)
	{
		if (*alst)
		{
			tmp = *alst;
			while (tmp)
			{
				if (tmp->next == NULL)
					tmp2 = tmp;
				tmp = tmp->next;
			}
			tmp = new;
			tmp2->next = new;
		}
		else
			*alst = new;
		new->next = NULL;
	}
}
