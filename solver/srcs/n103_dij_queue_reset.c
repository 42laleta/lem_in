#include "lem_in.h"

void	print_dij_queue(t_game *g, char *begin_line)
{
	int idx;

	idx = -1;
	ft_printf("%s_Queue:\n", begin_line);
	while (++idx < g->idx_dij)
	{
		ft_printf("%d(%d) -> ",
			g->dij_queue[idx]->idx, g->dij_queue[idx]->val_dij);
	}
	ft_printf("\n");
}

void	reset_dij_queue(t_game *g)
{
	g->dij_time += 1;
	g->rooms[g->start]->last_dij = g->dij_time;
	g->rooms[g->start]->from_dij = g->start;
	g->rooms[g->start]->val_dij = 0;
	g->rooms[g->start]->pulled_dij = 0;
	g->rooms[g->start]->updated_dij = 0;
	g->rooms[g->start]->look_dij = 0;
	g->idx_dij = 0;
	push_simple_dij_queue(g, g->start);
}
