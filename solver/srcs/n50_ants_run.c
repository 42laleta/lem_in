#include "lem_in.h"

int		sort_move(void *input)
{
	return ((t_ant_move *)input)->ant;
}

void	sort_output(t_game *g)
{
	int idx;

	idx = -1;
	while (++idx < g->idx_move)
		g->move_sdw[idx] = &(g->move_line[idx]);
	bubble_sort((void **)(g->move_sdw), g->idx_move, &sort_move);
}

void	print_line(t_game *g, int *run_happend)
{
	int idx;

	idx = -1;
	while (++idx < g->idx_move)
	{
		if (idx == 0)
			ft_printf("L%d-%s", g->move_sdw[idx]->ant,
			g->rooms[g->move_sdw[idx]->id_room]->name);
		else
			ft_printf(" L%d-%s", g->move_sdw[idx]->ant,
			g->rooms[g->move_sdw[idx]->id_room]->name);
	}
	if (idx > 0)
		*run_happend = 1;
	if (*run_happend)
	{
		if (g->space_end_line)
			ft_printf(" ");
		ft_printf("\n");
	}
}

void	ants_run(t_game *g)
{
	int run_happend;
	int idx;

	run_happend = 1;
	while (run_happend)
	{
		run_happend = 0;
		idx = g->idx_path;
		g->idx_move = 0;
		while (--idx > -1)
			move(g, idx);
		sort_output(g);
		print_line(g, &run_happend);
	}
}

int		virtual_ants_run(t_game *g)
{
	int		out;
	int		virtual_ants;
	int		idx;
	t_path	*path;

	if (g->idx_path < 1)
		return (-1);
	out = 0;
	virtual_ants = 0;
	while (virtual_ants < g->ants)
	{
		idx = g->idx_path;
		while (--idx > -1)
		{
			path = g->sol_path[idx];
			if (g->ants - virtual_ants > path->trigger)
				virtual_ants += 1;
		}
		out += 1;
	}
	path = g->sol_path[0];
	out += path->len - 1;
	return (out);
}
