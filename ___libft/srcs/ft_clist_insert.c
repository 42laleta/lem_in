/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clist_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 13:17:40 by fchanal           #+#    #+#             */
/*   Updated: 2017/01/03 18:47:39 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2libft.h"

t_list	*ft_clist_insert(t_clist *clist, t_list *current, void *data)
{
	t_list	*new;
	t_list	*tmp;

	if (!clist || !current)
		return (NULL);
	if (!(new = ft_clist_new(clist, data)))
		return (NULL);
	if (current->next)
		tmp = current->next;
	else
		tmp = current;
	current->next = new;
	new->next = tmp;
	return (new);
}
