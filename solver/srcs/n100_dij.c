#include "lem_in.h"

void	nothing_doto(t_game *g)
{
	if (g->debug_dij_decision)
		ft_printf("\t\tNOTHING_TO_DO\n");
}

void	processing_pulled_room(t_game *g, t_room *room)
{
	t_list		*node;
	t_list		pseudo_start;
	t_conn_dij	*c_dij;

	room->pulled_dij = 1;
	pseudo_start.next = room->conn_dij;
	node = &(pseudo_start);
	while ((node = node->next))
	{
		c_dij = (t_conn_dij *)(node->content);
		if (g->debug_dij_decision)
			ft_printf("\n\tadd_next?%d\n", c_dij->room->idx);
		if (edge_delete(g, c_dij))
			continue ;
		else if (room_pulled(g, c_dij))
			continue ;
		else if (roomlook_n_edgenotfree(g, room, c_dij))
			continue ;
		else if (push_to_queue(g, room, c_dij))
			continue ;
		else if (just_update_value(g, room, c_dij))
			continue ;
		else
			nothing_doto(g);
	}
}

int		dij(t_game *g)
{
	int			num_pull;
	int			id_room;
	t_room		*room;

	num_pull = 0;
	reset_dij_queue(g);
	while ((id_room = pull_dij_queue(g)) != -1)
	{
		num_pull += 1;
		room = g->rooms[id_room];
		processing_pulled_room(g, room);
		back_bubble_sort((void **)(g->dij_queue), g->idx_dij,
			&to_switch_room_dij);
	}
	if (g->debug_dij_num_pull)
		ft_printf("num_pull= %2d\n", num_pull);
	if (g->dij_time != g->rooms[g->end]->last_dij)
		return (0);
	return (num_pull);
}

int		suurballe(t_game *g)
{
	while (dij(g) > 1)
	{
		update_back_path(g);
		update_rest_dij(g);
		show_all_dij(g);
		calc_backward_dij(g);
		reset_bfs(g);
	}
	return (1);
}
