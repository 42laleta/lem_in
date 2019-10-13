/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 21:39:15 by laleta            #+#    #+#             */
/*   Updated: 2019/10/10 03:48:36 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

void	destroy_world(t_world *world)
{
	if (world->room_norm_ar)
		free(world->room_norm_ar);
	if (world->room_pixl_ar)
		free(world->room_pixl_ar);
	if (world->link_ar)
		free(world->link_ar);
	if (world->step_list)
		free_step_list(&world->step_list);
	if (world->view)
		free(world->view);
	if (world->prog)
	{
		if (world->prog->prog_room)
			glDeleteProgram(world->prog->prog_room);
		if (world->prog->prog_link)
			glDeleteProgram(world->prog->prog_link);
		free(world->prog);
	}
	if (world->win_2d)
		sfRenderWindow_destroy(world->win_2d);
	if (world->win_3d)
		sfRenderWindow_destroy(world->win_3d);
	if (world->rndr_sprite)
		sfSprite_destroy(world->rndr_sprite);
	if (world->rndr_texture)
		sfRenderTexture_destroy(world->rndr_texture);
	if (world->vbo_link)
		glDeleteBuffers(1, &(world->vbo_link));
}

void	free_room_list(t_room **room_list)
{
	t_room	*room;
	t_room	*clear;

	if (!(*room_list))
		return ;
	room = *room_list;
	while (room)
	{
		clear = room;
		room = room->next;
		free(clear);
	}
	room_list = NULL;
}

void	free_link_list(t_link **link_list)
{
	t_link	*link;
	t_link	*clear;

	if (!(*link_list))
		return ;
	link = *link_list;
	while (link)
	{
		clear = link;
		link = link->next;
		free(clear);
	}
	link_list = NULL;
}

void	free_step_list(t_step **step_list)
{
	t_step	*step;
	t_step	*clear;

	if (!(*step_list))
		return ;
	step = *step_list;
	while (step)
	{
		clear = step;
		step = step->next;
		free(clear->pos_ar);
		free(clear);
	}
	step_list = NULL;
}
