#include "lem_in.h"

int		edge_delete(t_game *g, t_conn_dij *c_dij)
{
	if (c_dij->state == -2)
	{
		if (g->debug_dij_decision)
			ft_printf("\t\tDELETED\n");
		return (1);
	}
	return (0);
}

int		room_pulled(t_game *g, t_conn_dij *c_dij)
{
	t_room		*update;

	update = c_dij->room;
	if (update->last_dij == g->dij_time && update->pulled_dij)
	{
		if (g->debug_dij_decision)
			ft_printf("\t\tPULLED\n");
		return (1);
	}
	return (0);
}

int		roomlook_n_edgenotfree(t_game *g, t_room *room, t_conn_dij *c_dij)
{
	if (room->look_dij && c_dij->state != 1)
	{
		if (g->debug_dij_decision)
			ft_printf("\t\tLOOKED\n");
		return (1);
	}
	return (0);
}

int		push_to_queue(t_game *g, t_room *room, t_conn_dij *c_dij)
{
	t_room		*update;
	int			tmp_val;

	tmp_val = room->val_dij + c_dij->wgh;
	update = c_dij->room;
	if (update->last_dij != g->dij_time)
	{
		if (g->debug_dij_decision)
			ft_printf("\t\tPUSH\n");
		update->last_dij = g->dij_time;
		update->val_dij = tmp_val;
		update->from_dij = room->idx;
		update->pulled_dij = 0;
		update->updated_dij = 0;
		if (c_dij->state == -1)
			update->look_dij = 1;
		else
			update->look_dij = 0;
		push_simple_dij_queue(g, update->idx);
		return (1);
	}
	return (0);
}

int		just_update_value(t_game *g, t_room *room, t_conn_dij *c_dij)
{
	t_room		*update;
	int			tmp_val;

	tmp_val = room->val_dij + c_dij->wgh;
	update = c_dij->room;
	if (tmp_val < update->val_dij)
	{
		if (g->debug_dij_decision)
			ft_printf("\t\tUPDATE value %d vs %d - org\n",
				tmp_val, update->val_dij);
		update->val_dij = tmp_val;
		update->from_dij = room->idx;
		return (1);
	}
	return (0);
}
