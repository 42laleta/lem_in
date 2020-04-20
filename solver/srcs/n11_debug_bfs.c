#include "lem_in.h"

void	show_bfs(t_game *g)
{
	int *queue;
	int top;
	int idx;

	if (g->active_bfs == 2)
	{
		queue = g->bfs_2_queue;
		top = g->top_2_bfs;
	}
	else
	{
		queue = g->bfs_1_queue;
		top = g->top_1_bfs;
	}
	idx = -1;
	ft_printf("BFS: ");
	while (++idx + g->bfs_idx < top)
		ft_printf(" %2d ", queue[idx + g->bfs_idx]);
	ft_printf("\n");
}

void	show_room_path(t_game *g, int start)
{
	int next;

	ft_printf(" -> %2d", start);
	if (start == g->start)
		return ;
	next = g->rooms[start]->path;
	while (next != -1 && next != g->start)
	{
		ft_printf(" -> %2d", next);
		if (next == g->start)
			break ;
		next = g->rooms[next]->path;
	}
	ft_printf(" -> %2d", g->start);
}
