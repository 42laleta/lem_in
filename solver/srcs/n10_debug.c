#include "lem_in.h"

void	show_room(t_room *room)
{
	ft_printf("idx      = \t%d\n", room->idx);
	ft_printf("name     = \t%s\n", room->name);
	ft_printf("x        = \t%d\n", room->x);
	ft_printf("y        = \t%d\n", room->y);
	ft_printf("num_conn = \t%d\n", room->num_conn);
	ft_printf("\n");
}

void	show_room_elem(t_list *elem)
{
	show_room(elem->content);
}

void	show_lst_room(t_game *game)
{
	ft_lstiter(game->lst_rooms, &show_room_elem);
}

void	show_game(t_game *game)
{
	ft_printf("\t >>>> GAME\n");
	ft_printf("\t\t\tants       = \t%d\n", game->ants);
	ft_printf("\t\t\tstart      = \t%d\n", game->start);
	ft_printf("\t\t\tend        = \t%d\n", game->end);
	ft_printf("\t\t\tnum_vertex = \t%d\n", game->num_vertex);
	ft_printf("\t\t\tpath_lim   = \t%d\n", game->path_lim);
	ft_printf("\t <<<< GAME\n\n");
}
