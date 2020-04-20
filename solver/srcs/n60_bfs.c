#include "lem_in.h"

int		init_bfs(t_game *g)
{
	g->bfs_1_queue = (int *)malloc(sizeof(int) * g->num_vertex);
	if (add_mstack(g->bfs_1_queue))
		return (INPUT_ERR_MALLOC);
	g->bfs_2_queue = (int *)malloc(sizeof(int) * g->num_vertex);
	if (add_mstack(g->bfs_2_queue))
		return (INPUT_ERR_MALLOC);
	g->top_1_bfs = 0;
	g->top_2_bfs = 0;
	g->active_bfs = 2;
	g->bfs_idx = 0;
	g->bfs_level = 1;
	g->backward_level = 0;
	g->best_backward_level = 0;
	g->best_result = -1;
	return (0);
}

void	add_next_bfs(t_game *g, int room)
{
	if (g->active_bfs == 2)
	{
		g->bfs_1_queue[g->top_1_bfs] = room;
		g->top_1_bfs += 1;
	}
	else
	{
		g->bfs_2_queue[g->top_2_bfs] = room;
		g->top_2_bfs += 1;
	}
}

int		get_bfs(t_game *g)
{
	int *queue;
	int top;

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
	if (g->bfs_idx >= top)
		return (-1);
	g->bfs_idx += 1;
	return (queue[g->bfs_idx - 1]);
}

int		switch_bfs(t_game *g)
{
	int out;

	out = 1;
	if (g->active_bfs == 2 && g->top_1_bfs == 0)
		out = 0;
	if (g->active_bfs == 1 && g->top_2_bfs == 0)
		out = 0;
	if (g->active_bfs == 2)
	{
		g->active_bfs = 1;
		g->top_2_bfs = 0;
	}
	else
	{
		g->active_bfs = 2;
		g->top_1_bfs = 0;
	}
	g->bfs_idx = 0;
	return (out);
}

void	reset_bfs(t_game *g)
{
	switch_bfs(g);
	g->bfs_level += 1;
	g->rooms[g->start]->bfs_r_step = g->bfs_level;
	add_next_bfs(g, g->start);
}
