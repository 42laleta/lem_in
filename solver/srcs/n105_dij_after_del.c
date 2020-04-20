#include "lem_in.h"

int		ft_del_conn_dij(t_list *lst, int trg)
{
	t_conn_dij	*c_dij;

	while (lst)
	{
		c_dij = (t_conn_dij *)(lst->content);
		if (c_dij->room->idx == trg)
		{
			c_dij->state = -2;
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int		ft_del_conn_dij_real(t_list **lst, int trg)
{
	t_list *to_del;

	if (!lst || !*lst)
		return (0);
	if (((t_conn_dij *)((*lst)->content))->room->idx == trg)
	{
		to_del = *lst;
		*lst = (*lst)->next;
		if (to_del->content)
			free(to_del->content);
		free(to_del);
		return (1);
	}
	if (((*lst)->next)
	&& ((t_conn_dij *)(((*lst)->next)->content))->room->idx == trg)
	{
		to_del = (*lst)->next;
		(*lst)->next = to_del->next;
		if (to_del->content)
			free(to_del->content);
		free(to_del);
		return (1);
	}
	return (ft_del_conn_dij_real(&((*lst)->next), trg));
}

/*
** ft_del_conn_dij can replace by ft_del_conn_dij_real
*/

void	delete_dir_path(t_game *g, int trg, int before)
{
	t_room *room;

	room = g->rooms[before];
	ft_del_conn_dij(room->conn_dij, trg);
}
