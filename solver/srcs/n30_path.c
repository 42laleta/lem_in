#include "lem_in.h"

void	show_stats_load(t_game *g)
{
	ft_printf("💾 total_capacity = %3d vs %-3d = ants\n",
		calc_capacity(g), g->ants);
	ft_printf("💾 total_len = \t\t\t%3d (%3d) 🗾\n",
		calc_total_len(g), g->idx_path);
}

void	show_stats(t_game *g)
{
	ft_printf("total_capacity = %3d vs %-3d = ants\n",
		calc_capacity(g), g->ants);
	ft_printf("total_len = \t\t\t%3d (%3d) 🗾\n",
		calc_total_len(g), g->idx_path);
}

void	show_sol_path(t_game *g)
{
	int idx;

	idx = -1;
	while (++idx < g->idx_path)
	{
		ft_printf("idx=%3d ", idx);
		ft_printf("len=%3d ", g->sol_path[idx]->len);
		ft_printf("tri=%3d : ", g->sol_path[idx]->trigger);
		ft_printf("%2d", g->end);
		show_room_path(g, g->sol_path[idx]->from_end->idx);
		ft_printf("\n");
	}
}
