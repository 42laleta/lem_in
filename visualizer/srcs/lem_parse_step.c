#include "lem_visual.h"

t_step					*create_step(uint32_t *pos_ar, t_world *world)
{
	t_step	*step;

	if (!(step = (t_step*)malloc(sizeof(t_step))))
		return (NULL);
	world->step_cnt++;
	step->pos_ar = pos_ar;
	step->next = NULL;
	return (step);
}

static inline int8_t	fill_pos_ar(char *str, t_room *room_list,
															uint32_t *pos_ar)
{
	char		**subtab;
	t_room		*room;

	if (!(subtab = ft_strsplit(str, '-')))
		return (0);
	room = room_list;
	while (room)
	{
		if (!ft_strcmp(subtab[1], room->name))
			pos_ar[ft_atoi(subtab[0] + 1) - 1] = room->num;
		room = room->next;
	}
	ft_free_wordtab(subtab);
	return (1);
}

int8_t					add_step(char *s, t_step *step_list, t_room *room_list,
																t_world *world)
{
	char		**tab;
	uint32_t	*pos_ar;
	int32_t		i;

	if (!(pos_ar = (uint32_t*)malloc(sizeof(uint32_t) * world->ant_cnt)))
		return (0);
	while (step_list->next)
		step_list = step_list->next;
	i = -1;
	while (++i < world->ant_cnt)
		pos_ar[i] = step_list->pos_ar[i];
	if (!(tab = ft_strsplit(s, ' ')))
		return (0);
	i = -1;
	while (tab[++i])
	{
		if (!fill_pos_ar(tab[i], room_list, pos_ar))
			break ;
	}
	ft_free_wordtab(tab);
	if (!(step_list->next = create_step(pos_ar, world)))
		return (0);
	return (1);
}

int8_t					parse_step(t_room *room_list, t_step **step_list,
																t_world *world)
{
	char		*s;
	int32_t		ret;
	int32_t		i;
	uint32_t	*pos_ar;

	i = -1;
	if (!(pos_ar = (uint32_t*)malloc(sizeof(uint32_t) * world->ant_cnt)))
		return (0);
	while (++i < world->ant_cnt)
		pos_ar[i] = world->start_room;
	if (!(*step_list = create_step(pos_ar, world)))
		return (0);
	while ((ret = get_next_line(0, &s)) && *s != '\n' && *s != 0)
	{
		if (*s != '#')
			if (!add_step(s, *step_list, room_list, world))
			{
				free(s);
				return (0);
			}
		free(s);
	}
	if (ret > 0)
		free(s);
	return (1);
}
