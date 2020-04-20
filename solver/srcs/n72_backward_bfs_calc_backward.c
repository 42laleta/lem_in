#include "lem_in.h"

void	add_path_to_sol(t_game *g, int trg, int len)
{
	t_path	*path;

	path = g->sol_path[g->idx_path];
	path->from_end = g->rooms[trg];
	path->len = len;
	path->trigger = calc_trigger(g, g->idx_path);
	g->idx_path += 1;
}

void	debug_part(t_game *g, int tmp)
{
	if (g->debug_magic || g->debug_magic_stats)
	{
		if (g->debug_magic)
			show_sol_path(g);
		if (g->debug_magic_stats)
			show_stats(g);
		ft_printf("BFS_backward finished  🎯 %3d 🎯\n\n\n", tmp);
	}
}

void	best_check(t_game *g, int *tmp)
{
	*tmp = virtual_ants_run(g);
	if (g->best_result < 0 || g->best_result > *tmp)
	{
		g->best_result = *tmp;
		g->best_backward_level = g->backward_level;
		save_best(g);
	}
}
