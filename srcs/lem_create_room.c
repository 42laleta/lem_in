/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_create_room.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 01:43:34 by laleta            #+#    #+#             */
/*   Updated: 2019/10/10 01:44:10 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

static inline void	set_color(t_room *room, int8_t color)
{
	if (color == CL_START)
	{
		room->color.x = 1.0;
		room->color.y = 0.0;
		room->color.z = 0.0;
	}
	else if (color == CL_END)
	{
		room->color.x = 0.0;
		room->color.y = 1.0;
		room->color.z = 0.0;
	}
	else
	{
		room->color.x = 0.5;
		room->color.y = 0.7;
		room->color.z = 0.9;
	}
}

t_room				*create_room(char *name, sfVector2i coord, int8_t color,
																t_world *world)
{
	t_room			*room;
	static uint8_t	num;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	world->crd_max.x = coord.x > world->crd_max.x ? coord.x : world->crd_max.x;
	world->crd_max.y = coord.y > world->crd_max.y ? coord.y : world->crd_max.y;
	world->crd_min.x = coord.x < world->crd_min.x ? coord.x : world->crd_min.x;
	world->crd_min.y = coord.y < world->crd_min.y ? coord.y : world->crd_min.y;
	world->room_cnt++;
	ft_strlcpy(room->name, name, LM_NAME_MAX);
	room->num = num++;
	if (color == CL_START)
		world->start_room = room->num;
	room->coord.x = coord.x;
	room->coord.y = coord.y;
	room->coord.z = rand_minus_one_one();
	set_color(room, color);
	room->next = NULL;
	return (room);
}
