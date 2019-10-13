/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clist_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 17:36:14 by fchanal           #+#    #+#             */
/*   Updated: 2017/01/03 12:28:54 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2libft.h"

t_list	*ft_clist_new(t_clist *clist, void *data)
{
	t_list	*tmp;

	if (!clist || !(tmp = (t_list*)malloc(sizeof(*tmp))))
		return (NULL);
	tmp->data = data;
	tmp->next = clist->parent_node;
	if (!clist->parent_node)
	{
		clist->parent_node = tmp;
		clist->list = tmp;
	}
	++(clist->list_size);
	return (tmp);
}
