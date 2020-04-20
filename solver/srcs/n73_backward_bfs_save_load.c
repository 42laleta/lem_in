#include "lem_in.h"

void	save_best(t_game *g)
{
	int		idx;
	t_room	*room;
	t_path	*org;
	t_path	*mem;

	idx = -1;
	g->best_idx_path = g->idx_path;
	while (++idx < g->best_idx_path)
	{
		mem = g->best_sol_path[idx];
		org = g->sol_path[idx];
		mem->from_end = org->from_end;
		mem->len = org->len;
		mem->trigger = org->trigger;
	}
	while (--idx > -1)
	{
		room = g->sol_path[idx]->from_end;
		while (room->idx != g->start)
		{
			room->best_hold_backward = room->hold_backward;
			room->best_path = room->path;
			room = g->rooms[room->path];
		}
	}
}

void	load_best_path(t_game *g)
{
	int		idx;
	t_room	*room;
	t_path	*org;
	t_path	*mem;

	idx = -1;
	g->idx_path = g->best_idx_path;
	while (++idx < g->idx_path)
	{
		mem = g->best_sol_path[idx];
		org = g->sol_path[idx];
		org->from_end = mem->from_end;
		org->len = mem->len;
		org->trigger = mem->trigger;
	}
	while (--idx > -1)
	{
		room = g->sol_path[idx]->from_end;
		while (room->idx != g->start)
		{
			room->hold_backward = room->best_hold_backward;
			room->path = room->best_path;
			room = g->rooms[room->best_path];
		}
	}
}
