#include "lem_in.h"

int		set_path_lim(t_game *game)
{
	int		idx;
	t_path	*path;

	game->path_lim = game->rooms[game->start]->num_conn;
	if (game->path_lim > game->rooms[game->end]->num_conn)
		game->path_lim = game->rooms[game->end]->num_conn;
	game->sol_path = (t_path **)malloc(sizeof(t_path *) * game->path_lim);
	game->best_sol_path = (t_path **)malloc(sizeof(t_path *) * game->path_lim);
	if (add_mstack(game->sol_path) || add_mstack(game->best_sol_path))
		return (INPUT_ERR_MALLOC);
	idx = -1;
	while (++idx < game->path_lim)
	{
		path = (t_path *)malloc(sizeof(t_path));
		if (add_mstack(path))
			return (INPUT_ERR_MALLOC);
		game->sol_path[idx] = path;
		path = (t_path *)malloc(sizeof(t_path));
		if (add_mstack(path))
			return (INPUT_ERR_MALLOC);
		game->best_sol_path[idx] = path;
	}
	game->idx_path = 0;
	game->best_idx_path = 0;
	return (0);
}

int		name_to_idx(t_game *game, char **words, int *node1, int *node2)
{
	char	*name1;
	char	*name2;
	t_list	*search;

	name1 = words[0];
	name2 = words[1];
	*node1 = -1;
	*node2 = -1;
	search = game->lst_rooms;
	while (search && !(*node1 != -1 && *node2 != -1))
	{
		if (ft_strcmp(((t_room *)search->content)->name, name1) == 0)
			*node1 = ((t_room *)search->content)->idx;
		if (ft_strcmp(((t_room *)search->content)->name, name2) == 0)
			*node2 = ((t_room *)search->content)->idx;
		search = search->next;
	}
	if (*node1 == -1 || *node2 == -1)
	{
		if (game->debug_error)
			ft_printf("%s - %s\n", words[0], words[1]);
		return (INPUT_ERR_VERTEX_NOT_FOUND);
	}
	return (0);
}

int		set_conn_dij(t_game *g, int node1, int node2)
{
	t_room		*room;
	t_list		*to_add;
	t_conn_dij	*conn_dij;

	if (check_same_edge_dij(g, node1, node2))
		return (INPUT_ERR_SAME_EDGE);
	conn_dij = (t_conn_dij *)malloc(sizeof(t_conn_dij));
	if (add_mstack(conn_dij))
		return (INPUT_ERR_MALLOC);
	to_add = ft_lstnew(NULL, 0);
	if (add_mstack(to_add))
		return (INPUT_ERR_MALLOC);
	conn_dij->room = g->rooms[node2];
	conn_dij->wgh = 1;
	conn_dij->state = 0;
	to_add->content = conn_dij;
	to_add->content_size = node2;
	room = g->rooms[node1];
	ft_lstadd(&(room->conn_dij), to_add);
	room->num_conn += 1;
	if (g->end == node2)
		room->connect_to_end = 1;
	return (0);
}

int		set_edge_dij(t_game *g, int node1, int node2)
{
	if (set_conn_dij(g, node1, node2))
		return (INPUT_ERR_MALLOC);
	if (set_conn_dij(g, node2, node1))
		return (INPUT_ERR_MALLOC);
	return (0);
}

int		set_edge(t_game *game, char *line)
{
	char	**words;
	int		idx;
	int		node1;
	int		node2;

	words = ft_strsplit(line, '-');
	if (words == NULL)
		return (INPUT_ERR_SPLIT_NULL);
	idx = 0;
	while (words[idx])
		++idx;
	if (idx != 2)
		return (clean_words(&words, idx, INPUT_ERR_EDGE));
	if (ft_strcmp(words[0], words[1]) == 0)
		return (clean_words(&words, idx, INPUT_ERR_EDGE_SAME_VERTEX));
	if (name_to_idx(game, words, &node1, &node2))
		return (clean_words(&words, idx, INPUT_ERR_VERTEX_NOT_FOUND));
	clean_words(&words, idx, 0);
	if (set_edge_dij(game, node1, node2))
		return (INPUT_ERR_SAME_EDGE);
	return (0);
}
