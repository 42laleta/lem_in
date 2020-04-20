#include "lem_in.h"

int		read_input(t_game *g, int argc, char *argv[], int *fd)
{
	int		input_err;

	*fd = get_fd(argc, argv);
	if ((input_err = input(g, *fd)) != 0)
	{
		if (g->debug_error)
			ft_printf("NOT ok, INPUT_ERR=%d\n", input_err);
		else
			ft_printf("ERROR\n");
		clean_out(g);
		free_all_mstack();
		return (1);
	}
	return (0);
}

int		check_and_malloc4sol(t_game *g)
{
	if (g->start == -1 || g->end == -1 || g->rooms == NULL
		|| g->rooms[g->end]->num_conn < 1
		|| g->rooms[g->start]->num_conn < 1)
	{
		ft_printf("ERROR\n");
		clean_out(g);
		free_all_mstack();
		return (1);
	}
	if (set_path_lim(g))
	{
		clean_out(g);
		free_all_mstack();
		return (1);
	}
	return (0);
}

void	debug_show(t_game *g)
{
	if (g->debug_lst_room)
		show_lst_room(g);
	if (g->debug_game)
		show_game(g);
}
