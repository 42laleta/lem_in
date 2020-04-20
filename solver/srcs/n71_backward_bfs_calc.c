#include "lem_in.h"

int		calc_trigger(t_game *g, int idx_sol_path)
{
	int		idx;
	int		out;
	int		num_step;

	if (idx_sol_path == 0)
		return (0);
	out = 0;
	idx = -1;
	num_step = g->sol_path[idx_sol_path]->len;
	while (++idx < idx_sol_path)
		out += num_step - g->sol_path[idx]->len + 1;
	return (out);
}

int		calc_capacity(t_game *g)
{
	int		idx;
	int		out;
	int		num_step;

	if (g->idx_path == 0)
		return (0);
	out = 0;
	idx = -1;
	num_step = g->sol_path[g->idx_path - 1]->len;
	while (++idx < g->idx_path)
		out += num_step - g->sol_path[idx]->len + 1;
	return (out);
}

int		calc_total_len(t_game *g)
{
	int		idx;
	int		out;

	if (g->idx_path == 0)
		return (0);
	out = 0;
	idx = -1;
	while (++idx < g->idx_path)
		out += g->sol_path[idx]->len;
	return (out);
}
