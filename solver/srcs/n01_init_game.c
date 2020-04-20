#include "lem_in.h"

void	init_game_base(t_game *g)
{
	g->lst_rooms = NULL;
	g->rooms = NULL;
	g->out_or_error = NULL;
	g->start = -1;
	g->end = -1;
	g->ants = -1;
	g->num_vertex = -1;
	g->path_lim = -1;
	g->ant_in_run = 0;
	g->dij_queue = NULL;
	g->idx_dij = 0;
	g->dij_time = 0;
}

void	init_game_debug(t_game *g)
{
	g->debug_error = 0;
	g->debug_lst_room = 0;
	g->debug_rooms = 0;
	g->debug_game = 0;
	g->debug_after_init = 0;
	g->debug_next_bfs = 0;
	g->debug_update_netword = 0;
	g->debug_backward_find = 0;
	g->debug_magic = 0;
	g->debug_magic_stats = 0;
	g->debug_magic_final = 0;
	g->debug_levels = 0;
	g->debug_real_bfs = 0;
	g->debug_queue = 0;
	g->debug_dij_decision = 0;
	g->debug_dij_after = 0;
	g->debug_dij_all = 0;
	g->debug_dij_num_pull = 0;
}

void	init_game_param(t_game *g)
{
	g->free_edge_noupdate = 0;
	g->dij_touch_noupdate = 0;
	g->capacity_check = 0;
	g->space_end_line = 0;
	g->no_unknows_cmd = 1;
	g->bfs_ants_run = 0;
	g->queue_search = 0;
	g->print_map = 1;
	g->to_the_run = 1;
}

void	init_game(t_game *game)
{
	init_game_base(game);
	init_game_debug(game);
	init_game_param(game);
}

int		get_fd(int argc, char *argv[])
{
	int fd;

	if (argc > 1 && (fd = open(argv[1], O_RDONLY)) > 0)
		return (fd);
	return (0);
}
