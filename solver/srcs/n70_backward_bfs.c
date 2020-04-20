#include "lem_in.h"

int		apply_dfs_backward(t_game *g, int room)
{
	int		next;
	int		from;
	int		last;

	if (g->debug_backward_find)
		ft_printf("start [%2d -> %2d", g->start, room);
	next = g->rooms[room]->path;
	from = g->start;
	last = room;
	while (room != g->end && room != -1)
	{
		g->rooms[room]->hold_backward = g->backward_level;
		g->rooms[room]->path = from;
		from = room;
		last = room;
		room = next;
		next = g->rooms[room]->path;
		if (g->debug_backward_find)
			ft_printf("-> %2d", room);
	}
	if (g->debug_backward_find)
		ft_printf(" ] end\n\n");
	return (last);
}

void	backward_bfs(t_game *g)
{
	switch_bfs(g);
	g->bfs_level += 1;
	g->backward_level += 1;
	g->rooms[g->end]->bfs_r_step = g->bfs_level;
	add_next_bfs(g, g->end);
}

void	reset_backward_bfs(t_game *g)
{
	switch_bfs(g);
	g->bfs_level += 1;
	g->rooms[g->end]->bfs_r_step = g->bfs_level;
	add_next_bfs(g, g->end);
}
