/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clist_del_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 12:32:18 by fchanal           #+#    #+#             */
/*   Updated: 2017/01/04 18:31:06 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2libft.h"

void	ft_clist_del_node(t_clist *clist, t_list **node, void (*del)(void**))
{
	t_list	*prev;
	t_list	*tmp;

	if (!node || !*node || !clist)
		return ;
	prev = ft_clist_find_prev(*node);
	tmp = (*node)->next;
	if (*node == clist->parent_node)
		clist->parent_node = tmp;
	if (del)
		del(&(*node)->data);
	free(*node);
	*node = NULL;
	--(clist->list_size);
	if (prev)
		prev->next = tmp;
	if (tmp == clist->parent_node)
		clist->list = tmp;
}
