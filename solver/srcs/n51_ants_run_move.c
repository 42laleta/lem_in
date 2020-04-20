#include "lem_in.h"

void	move_runner(t_game *g, t_room *from, t_room *to, int runner)
{
	if (to->idx != g->end)
		to->ant = runner;
	g->move_line[g->idx_move].ant = runner;
	g->move_line[g->idx_move].id_room = to->idx;
	g->idx_move += 1;
	from->ant = 0;
}

int		get_runner(t_game *g, t_path *path, t_room *from)
{
	int runner;

	runner = 0;
	if (from->idx == g->start)
	{
		if (g->ants - g->ant_in_run > path->trigger)
		{
			g->ant_in_run += 1;
			runner = g->ant_in_run;
		}
	}
	else
		runner = from->ant;
	return (runner);
}

void	move(t_game *g, int idx_path)
{
	t_path	*path;
	t_room	*from;
	t_room	*to;
	int		runner;

	path = g->sol_path[idx_path];
	to = g->rooms[g->end];
	from = g->sol_path[idx_path]->from_end;
	while (to->idx != g->start)
	{
		runner = get_runner(g, path, from);
		if (runner)
			move_runner(g, from, to, runner);
		to = from;
		if (from->idx != g->start)
			from = g->rooms[from->path];
	}
}
