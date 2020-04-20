#include "lem_in.h"

void	do_next_dij(t_game *g, t_conn_dij *conn, int room)
{
	conn->room->bfs_r_step = g->bfs_level;
	add_next_bfs(g, conn->room->idx);
	conn->room->path = room;
}

int		next_backward_bfs_dij(t_game *g)
{
	int			room;
	t_list		*node;
	t_conn_dij	*c_dij;
	t_list		pseudo_start;

	while ((room = get_bfs(g)) != -1)
	{
		pseudo_start.next = g->rooms[room]->conn_dij;
		node = &(pseudo_start);
		while ((node = node->next))
		{
			c_dij = (t_conn_dij *)(node->content);
			if (c_dij->state != 1)
				continue;
			if (c_dij->room->idx == g->start && room != g->end)
				return (apply_dfs_backward(g, room));
			else
			{
				if (c_dij->room->bfs_r_step < g->bfs_level
					&& c_dij->room->hold_backward < g->backward_level)
					do_next_dij(g, c_dij, room);
			}
		}
	}
	return (-1);
}

void	calc_backward_dij(t_game *g)
{
	int		len;
	int		out;
	int		tmp;

	g->backward_level += 1;
	backward_bfs(g);
	len = 0;
	g->idx_path = 0;
	if (g->rooms[g->start]->connect_to_end == 1)
		add_path_to_sol(g, g->start, 1);
	while (switch_bfs(g))
	{
		len += 1;
		if ((out = next_backward_bfs_dij(g)) != -1)
		{
			if (g->debug_backward_find)
				ft_printf("🏅  new back path LEN=%2d\n", len);
			add_path_to_sol(g, out, len);
			len = 0;
			reset_backward_bfs(g);
		}
	}
	best_check(g, &tmp);
	debug_part(g, tmp);
}
