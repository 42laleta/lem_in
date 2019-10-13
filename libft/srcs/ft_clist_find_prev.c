/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clist_find_prev.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 12:33:25 by fchanal           #+#    #+#             */
/*   Updated: 2017/01/02 12:33:42 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2libft.h"

t_list	*ft_clist_find_prev(t_list *wall)
{
	t_list	*list;

	if (!wall || !wall->next)
		return (NULL);
	list = wall->next;
	while (list->next != wall)
		list = list->next;
	return (list);
}
