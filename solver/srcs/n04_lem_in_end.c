#include "lem_in.h"

void	debug_show_after(t_game *g)
{
	if (g->debug_magic_final)
	{
		ft_printf("🏆\n\n");
		show_sol_path(g);
		show_stats(g);
		ft_printf("BFS_backward finished  🎯 %3d 🎯\n", virtual_ants_run(g));
		ft_printf("\n🏆  BFS finished\n\n");
	}
	if (g->debug_levels)
	{
		ft_printf("\nbfs_level     = %d", g->bfs_level);
		ft_printf("\nbackward_level= %d\n", g->backward_level);
		ft_printf("\npaths_found   = (%d/%d)\n", g->idx_path, g->path_lim);
	}
}

int		check_exist_path(t_game *g)
{
	if (g->idx_path == 0)
	{
		ft_printf("ERROR\n");
		clean_out(g);
		free_all_mstack();
		return (1);
	}
	g->move_line = (t_ant_move *)malloc(sizeof(t_ant_move) * calc_total_len(g));
	g->move_sdw = (t_ant_move **)malloc(sizeof(t_ant_move *)
		* calc_total_len(g));
	if (add_mstack(g->move_sdw) || add_mstack(g->move_line))
	{
		clean_out(g);
		free_all_mstack();
		return (INPUT_ERR_MALLOC);
	}
	return (0);
}

void	map_and_ants_run(t_game *g)
{
	if (g->print_map)
		print_and_clean(g);
	else
		clean_out(g);
	if (g->to_the_run)
		ants_run(g);
}
