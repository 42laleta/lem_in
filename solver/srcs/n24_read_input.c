#include "lem_in.h"

int		input(t_game *game, int fd)
{
	char	*line;
	int		cmd;
	int		rls_err;

	cmd = 0;
	while ((rls_err = get_next_line(fd, &line)) != 0)
	{
		if ((rls_err = check_and_save_map(game, line, rls_err)) > 0)
			return (rls_err);
		if (rls_err == -1)
			continue;
		if (line[0] == '#' && set_command(line, &cmd))
			continue;
		if (game->ants == -1)
		{
			if (set_number(line, &game->ants, 1))
				return (INPUT_ERR_ANTS);
			continue;
		}
		if ((rls_err = set_v_or_e(line, &cmd, game)))
			return (rls_err);
	}
	return (0);
}
