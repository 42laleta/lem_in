#include "lem_in.h"

void	look_income(t_game *g, int trg)
{
	t_room		*room;
	t_list		*node;
	t_list		*income_node;
	t_conn_dij	*income_c_dij;

	node = g->rooms[trg]->conn_dij;
	while (node)
	{
		room = ((t_conn_dij *)(node->content))->room;
		income_node = room->conn_dij;
		while (income_node)
		{
			income_c_dij = (t_conn_dij *)(income_node->content);
			if (income_c_dij->room->idx == trg
				&& income_c_dij->state != 1
				&& income_c_dij->state != -2)
			{
				income_c_dij->state = -1;
				break ;
			}
			income_node = income_node->next;
		}
		node = node->next;
	}
}

void	update_to_zero(t_game *g, int trg, int before)
{
	t_room		*room;
	t_list		*node;
	t_conn_dij	*c_dij;
	t_list		pseudo_start;

	room = g->rooms[trg];
	pseudo_start.next = room->conn_dij;
	node = &(pseudo_start);
	while ((node = node->next))
	{
		c_dij = (t_conn_dij *)(node->content);
		if (c_dij->state == -2)
			continue;
		if (c_dij->room->idx == before)
		{
			c_dij->wgh = 0;
			c_dij->state = 1;
			return ;
		}
	}
}

void	update_room_dij(t_game *g, int id_room, int except)
{
	t_room		*room;
	t_list		*node;
	t_list		pseudo_start;
	t_conn_dij	*c_dij;

	room = g->rooms[id_room];
	if (g->dij_touch_noupdate == 1 && room->last_dij != g->dij_time)
		return ;
	pseudo_start.next = room->conn_dij;
	node = &(pseudo_start);
	while ((node = node->next))
	{
		c_dij = (t_conn_dij *)(node->content);
		if (c_dij->room->idx == except)
			continue;
		if (g->free_edge_noupdate && c_dij->state == 1)
			continue;
		c_dij->wgh = (c_dij->wgh) - (c_dij->room->val_dij) + (room->val_dij);
	}
	g->rooms[id_room]->updated_dij = 1;
}

void	update_back_path(t_game *g)
{
	int trg;
	int before;

	trg = g->end;
	while (trg != g->start)
	{
		before = g->rooms[trg]->from_dij;
		update_to_zero(g, trg, before);
		delete_dir_path(g, trg, before);
		update_room_dij(g, trg, before);
		look_income(g, trg);
		trg = before;
	}
	update_room_dij(g, trg, -1);
	look_income(g, trg);
}

void	update_rest_dij(t_game *g)
{
	int idx;

	idx = -1;
	while (++idx < g->num_vertex)
	{
		if (g->rooms[idx]->last_dij == g->dij_time
			&& g->rooms[idx]->updated_dij != 1)
		{
			update_room_dij(g, idx, -1);
		}
	}
}
