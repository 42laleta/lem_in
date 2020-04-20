#include "lem_in.h"

int		clean_words(char ***words, int idx, int error)
{
	while (--idx > -1)
		free((*words)[idx]);
	free(*words);
	return (error);
}

int		check_valid_vetrex(char ***words_out, char *line, t_game *g)
{
	char	**words;
	int		idx;
	t_list	*lst_add;

	words = ft_strsplit(line, ' ');
	if (words == NULL)
		return (INPUT_ERR_SPLIT_NULL);
	idx = 0;
	while (words[idx])
		++idx;
	if (idx != 3)
		return (clean_words(&words, idx, INPUT_ERR_VERTEX));
	lst_add = g->lst_rooms;
	while (lst_add)
	{
		if (ft_strcmp(words[0], ((t_room *)(lst_add->content))->name) == 0)
			return (clean_words(&words, idx, INPUT_ERR_SAME_NAME_FOR_VERTEX));
		lst_add = lst_add->next;
	}
	*words_out = words;
	return (0);
}

int		add_vertex_to_list(char ***words, t_list **lst_add, t_room **room_add)
{
	*room_add = (t_room *)malloc(sizeof(t_room));
	if (add_mstack(*room_add))
		return (clean_words(words, 3, INPUT_ERR_NEW_ROOM));
	*lst_add = ft_lstnew(NULL, 0);
	if (add_mstack(*lst_add))
		return (clean_words(words, 3, INPUT_ERR_NEW_LIST));
	init_room(*room_add);
	if (set_number((*words)[2], &((*room_add)->y), 0))
		return (clean_words(words, 3, INPUT_ERR_COOR));
	if (set_number((*words)[1], &((*room_add)->x), 0))
		return (clean_words(words, 3, INPUT_ERR_COOR));
	(*room_add)->num_conn = 0;
	(*room_add)->name = ft_strdup((*words)[0]);
	clean_words(words, 3, 0);
	if (add_mstack((*room_add)->name))
		return (INPUT_ERR_MSTACK);
	return (0);
}

int		cmd_valid(t_game *g, int *cmd, int lst_idx)
{
	if (*cmd == 1)
	{
		if (g->start == -1)
			g->start = lst_idx;
		else
			return (INPUT_ERR_MULI_START_OR_END);
	}
	if (*cmd == 2)
	{
		if (g->end == -1)
			g->end = lst_idx;
		else
			return (INPUT_ERR_MULI_START_OR_END);
	}
	*cmd = 0;
	return (0);
}

int		set_vertex(char *line, int *cmd, t_game *game)
{
	char	**words;
	t_list	*lst_add;
	t_room	*room_add;
	int		lst_idx;
	int		err;

	if ((err = check_valid_vetrex(&words, line, game)))
		return (err);
	if ((err = add_vertex_to_list(&words, &lst_add, &room_add)))
		return (err);
	if (game->lst_rooms == NULL)
		lst_idx = 0;
	else
		lst_idx = game->lst_rooms->content_size + 1;
	room_add->idx = lst_idx;
	lst_add->content_size = lst_idx;
	lst_add->content = room_add;
	ft_lstadd(&(game->lst_rooms), lst_add);
	if ((err = cmd_valid(game, cmd, lst_idx)))
		return (err);
	return (0);
}
