#include "lem_in.h"

void	init_room(t_room *room)
{
	room->x = -1;
	room->y = -1;
	room->name = NULL;
	room->idx = -1;
	room->num_conn = 0;
	room->connect_to_end = 0;
	room->bfs_r_step = -1;
	room->ant = 0;
	room->path = -1;
	room->hold_backward = 0;
	room->best_path = -1;
	room->best_hold_backward = 0;
	room->conn_dij = NULL;
	room->last_dij = -1;
	room->pulled_dij = 0;
	room->from_dij = -1;
	room->val_dij = -1;
	room->can_look = -1;
	room->look_dij = 0;
}

int		set_vetrix_for_edge(t_game *game)
{
	t_list	*node;
	t_room	*rm;

	game->rooms = (t_room **)malloc(sizeof(t_room *) * (game->num_vertex + 1));
	if (add_mstack(game->rooms))
		return (INPUT_ERR_MALLOC);
	node = game->lst_rooms;
	while (node)
	{
		rm = node->content;
		game->rooms[node->content_size] = rm;
		node = node->next;
	}
	return (0);
}

int		end_of_set_vetrex(t_game *game)
{
	int to_set;

	to_set = ft_lstlen(game->lst_rooms);
	if (to_set < 2)
		return (INPUT_ERR_NUM_VERTEX);
	if (game->start == -1 || game->end == -1)
		return (INPUT_ERR_NO_END_START);
	game->num_vertex = to_set;
	return (0);
}

int		check_same_edge_dij(t_game *g, int node1, int node2)
{
	t_list	*tmp;

	tmp = g->rooms[node1]->conn_dij;
	while (tmp)
	{
		if (((t_conn_dij *)(tmp->content))->room->idx == node2)
			return (INPUT_ERR_SAME_EDGE);
		tmp = tmp->next;
	}
	return (0);
}
