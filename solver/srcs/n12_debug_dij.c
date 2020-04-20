#include "lem_in.h"

void	show_all_dij_job_line(t_game *g, int show_rooms, int line)
{
	t_room		*room;
	t_list		*node;
	t_conn_dij	*dij;
	int			idx;
	int			count_line;

	idx = -1;
	while (++idx < show_rooms && idx < g->num_vertex)
	{
		count_line = line;
		room = g->rooms[idx];
		node = room->conn_dij;
		while (node != NULL && --count_line > -1)
			node = node->next;
		if (node)
		{
			dij = (t_conn_dij *)(node->content);
			ft_printf("\t|-(%2d)-> %2d\t", dij->wgh, dij->room->idx);
		}
		else
			ft_printf("\t            \t");
	}
}

void	show_all_dij_job(t_game *g, int show_conns, int show_rooms)
{
	int			line;

	line = -1;
	while (++line < show_conns)
	{
		show_all_dij_job_line(g, show_rooms, line);
		ft_printf("\n");
	}
}

void	show_all_dij(t_game *g)
{
	int			idx;
	t_room		*room;

	if (g->debug_dij_all == 0)
		return ;
	ft_printf(">>>>\t show_all_dij\n\n");
	idx = -1;
	while (++idx < SHOW_ROOM && idx < g->num_vertex)
	{
		room = g->rooms[idx];
		ft_printf("%d-(%2d)->rm{%2d}\t\t",
			room->from_dij, room->val_dij, room->idx);
	}
	ft_printf("\n");
	idx = -1;
	while (++idx < SHOW_ROOM && idx < g->num_vertex)
		ft_printf("--------------\t\t");
	ft_printf("\n");
	show_all_dij_job(g, SHOW_CONN, SHOW_ROOM);
	ft_printf("\n<<<<\t show_all_dij\n");
}

void	show_all_dij_list_job(t_room *room)
{
	t_list		*node;
	t_conn_dij	*dij;
	char		c;

	node = room->conn_dij;
	while (node)
	{
		dij = (t_conn_dij *)(node->content);
		c = ' ';
		if (dij->state == 1)
			c = 'f';
		if (dij->state == -1)
			c = 'b';
		ft_printf("\t|_%c_-(%2d)-> %2d\n",
			c, dij->wgh, dij->room->idx);
		node = node->next;
	}
}

void	show_all_dij_list(t_game *g)
{
	int			idx;
	t_room		*room;

	idx = -1;
	ft_printf(">>>>\t show_all_dij\n\n");
	while (++idx < g->num_vertex)
	{
		room = g->rooms[idx];
		ft_printf("%d-(%2d)->rm{%2d}\n",
			room->from_dij, room->val_dij, room->idx);
		show_all_dij_list_job(room);
		ft_printf("\n");
	}
	ft_printf("\n<<<<\t show_all_dij\n");
}
