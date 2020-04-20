#include "lem_visual.h"

t_link					*create_link(int32_t *index, t_world *world)
{
	t_link	*link;

	if (!(link = (t_link*)malloc(sizeof(t_link))))
		return (NULL);
	world->link_cnt++;
	link->index.x = index[0];
	link->index.y = index[1];
	link->next = NULL;
	return (link);
}

static inline int8_t	add_link_aux(t_link **link_list, t_world *world,
																int32_t *index)
{
	t_link	*link;

	link = *link_list;
	if (!(*link_list))
	{
		if (!(*link_list = create_link(index, world)))
			return (0);
	}
	else
	{
		while (link->next)
		{
			if ((link->index.x == index[0] && link->index.y == index[1]) ||
		(link->next->index.x == index[0] && link->next->index.y == index[1]))
				return (1);
			link = link->next;
		}
		if (!(link->next = create_link(index, world)))
			return (0);
	}
	return (1);
}

int8_t					add_link(char *s, t_link **link_list, t_room *room_list,
																t_world *world)
{
	char		**tab;
	int8_t		link_point;
	int32_t		index[2];

	link_point = 0;
	if (!(tab = ft_strsplit(s, '-')))
		return (0);
	while (room_list && link_point != 2)
	{
		if (!ft_strcmp(tab[0], room_list->name) ||
			!ft_strcmp(tab[1], room_list->name))
			index[link_point++] = room_list->num;
		room_list = room_list->next;
	}
	ft_free_wordtab(tab);
	if (index[0] > index[1])
		swap_ar(index);
	if (!add_link_aux(link_list, world, index))
		return (0);
	return (1);
}

int8_t					parse_link(t_room *room_list, t_link **link_list,
													t_world *world, char *str)
{
	char	*s;
	int32_t	ret;

	if (!add_link(str, link_list, room_list, world))
	{
		free(str);
		return (0);
	}
	free(str);
	while ((ret = get_next_line(0, &s)) && *s != '\n' && *s != 0)
	{
		if (*s != '#')
		{
			if (!add_link(s, link_list, room_list, world))
			{
				free(s);
				return (0);
			}
		}
		free(s);
	}
	if (ret > 0)
		free(s);
	return (1);
}
