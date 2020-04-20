#include "lem_in.h"

void	debug_magic_stats(t_game *g)
{
	if (g->debug_magic_stats == 0)
		return ;
	show_stats_load(g);
	ft_printf("\t\t\t   lines_num = %d\n", virtual_ants_run(g));
}

void	debug_all_dij_list(t_game *g)
{
	if (g->debug_dij_after == 0)
		return ;
	show_all_dij_list(g);
}

int		main(int argc, char *argv[])
{
	t_game	game;
	int		fd;

	init_game(&game);
	if (read_input(&game, argc, argv, &fd))
		exit(1);
	if (check_and_malloc4sol(&game))
		exit(1);
	debug_show(&game);
	if (init_dij_queue(&game))
		return (INPUT_ERR_MALLOC);
	if (init_bfs(&game))
		return (INPUT_ERR_MALLOC);
	suurballe(&game);
	debug_all_dij_list(&game);
	load_best_path(&game);
	debug_magic_stats(&game);
	debug_show_after(&game);
	if (check_exist_path(&game))
		exit(1);
	map_and_ants_run(&game);
	if (fd > 0)
		close(fd);
	free_all_mstack();
	return (0);
}
