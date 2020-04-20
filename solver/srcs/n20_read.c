#include "lem_in.h"

int		set_number(char *line, int *ants, short positiv)
{
	*ants = ft_atoi(line);
	if (ft_nbrlen(*ants) != ft_strlen(line))
		return (1);
	if (ft_strlen(line) == 1 && (line[0] - 48 != *ants))
		return (1);
	if (positiv && *ants < 1)
		return (1);
	return (0);
}

int		set_command(char *line, int *cmd)
{
	if (ft_strcmp(line, "##start") == 0)
		*cmd = 1;
	if (ft_strcmp(line, "##end") == 0)
		*cmd = 2;
	return (1);
}

int		set_v_or_e(char *line, int *cmd, t_game *game)
{
	int err;

	if (ft_strstr(line, " ") != NULL)
	{
		if (game->num_vertex != -1)
			return (INPUT_ERR_MIXUP);
		return (set_vertex(line, cmd, game));
	}
	if (*cmd)
		return (INPUT_ERR_CMD_FOR_EDGE);
	if (game->num_vertex == -1)
	{
		if ((err = end_of_set_vetrex(game)) != 0)
			return (err);
		if (set_vetrix_for_edge(game))
			return (INPUT_ERR_END_PROCESS);
	}
	return (set_edge(game, line));
}

int		save_gnl(t_game *g, char *line)
{
	t_list	*save_line;

	save_line = ft_lstnew(NULL, 0);
	if (save_line == NULL)
		return (INPUT_ERR_NEW_LIST);
	save_line->content = line;
	ft_lstadd(&(g->out_or_error), save_line);
	return (0);
}

int		check_and_save_map(t_game *g, char *line, int rls)
{
	if (rls == -1)
		return (INPUT_ERR_GNL);
	if (line[0] == 'L')
		return (INPUT_ERR_L);
	if (g->no_unknows_cmd == 1
		&& ft_strstr(line, "##") == line
		&& ft_strstr(line, "###") != line
		&& ft_strcmp(line, "##end")
		&& ft_strcmp(line, "##start"))
	{
		free(line);
		return (-1);
	}
	if (save_gnl(g, line))
		return (INPUT_ERR_NEW_LIST);
	return (0);
}
