#include "lem_visual.h"

void					add_room(char *s, t_room **room_list, int8_t color,
																t_world *world)
{
	char			**tab;
	t_room			*room;
	sfVector2i		coord;

	room = *room_list;
	if (!(tab = ft_strsplit(s, ' ')))
		return ;
	if (!(*room_list))
	{
		coord.x = ft_atoi(tab[1]);
		coord.y = ft_atoi(tab[2]);
		*room_list = create_room(tab[0], coord, color, world);
	}
	else
	{
		while (room->next)
			room = room->next;
		coord.x = ft_atoi(tab[1]);
		coord.y = ft_atoi(tab[2]);
		room->next = create_room(tab[0], coord, color, world);
	}
	ft_free_wordtab(tab);
}

static inline void		parse_comment_line(char *str, t_room **room_list,
																t_world *world)
{
	char	*s;

	if (*(str + 1) == '#')
	{
		if (ft_strcmp(str, LM_START) == 0)
		{
			while (get_next_line(0, &s) && *s == '#')
				free(s);
			add_room(s, room_list, CL_START, world);
			free(s);
		}
		else if (ft_strcmp(str, LM_END) == 0)
		{
			while (get_next_line(0, &s) && *s == '#')
				free(s);
			add_room(s, room_list, CL_END, world);
			free(s);
		}
		free(str);
	}
	else
		free(str);
}

static inline int8_t	parse_error(t_world *world)
{
	char	*s;
	int32_t	ret;

	while ((ret = get_next_line(0, &s)) && *s == '#')
		free(s);
	if (ft_strcmp(s, LM_ERROR) == 0)
	{
		write(1, "ERROR\n", 6);
		if (ret > 0)
			free(s);
		return (1);
	}
	world->ant_cnt = ft_atoi(s);
	free(s);
	return (0);
}

int8_t					parse_room(t_room **room_list, t_link **link_list,
																t_world *world)
{
	char	*s;
	char	*fnd_dash;
	int32_t	ret;

	if (parse_error(world))
		return (0);
	while ((ret = get_next_line(0, &s)) && *s != 0 && *s != '\n')
	{
		if (*s == '#')
			parse_comment_line(s, room_list, world);
		else
		{
			if (*s == '-' || (*s != '-' && (!(fnd_dash = ft_strchr(s, '-')))) ||
							(*s != '-' && fnd_dash && *(fnd_dash - 1) == ' '))
				add_room(s, room_list, CL_DEFLT, world);
			else if (fnd_dash)
			{
				parse_link(*room_list, link_list, world, s);
				return (1);
			}
			free(s);
		}
	}
	ret > 0 ? free(s) : (void*)s;
	return (1);
}
