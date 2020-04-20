#include "lem_in.h"

int		init_dij_queue(t_game *g)
{
	g->dij_queue = (t_room **)malloc(sizeof(t_room *) * g->num_vertex);
	if (add_mstack(g->dij_queue))
		return (INPUT_ERR_MALLOC);
	g->idx_dij = 0;
	return (0);
}

int		to_switch_room_dij(void *cur, void *back)
{
	if (((t_room *)cur)->val_dij > ((t_room *)back)->val_dij)
		return (1);
	return (0);
}

void	push_dij_queue(t_game *g, int add)
{
	g->dij_queue[g->idx_dij] = g->rooms[add];
	g->idx_dij += 1;
	back_bubble_sort((void **)(g->dij_queue), g->idx_dij,
		&to_switch_room_dij);
	if (g->debug_queue)
		print_dij_queue(g, "PUSH");
}

void	push_simple_dij_queue(t_game *g, int add)
{
	g->dij_queue[g->idx_dij] = g->rooms[add];
	g->idx_dij += 1;
}

int		pull_dij_queue(t_game *g)
{
	int	out;

	if (g->idx_dij < 1)
		return (-1);
	out = g->dij_queue[g->idx_dij - 1]->idx;
	g->idx_dij -= 1;
	if (g->debug_queue)
	{
		print_dij_queue(g, "PULL");
		ft_printf("\t\tout = %d\n", out);
	}
	return (out);
}
