/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 22:09:42 by laleta            #+#    #+#             */
/*   Updated: 2019/10/07 22:52:34 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

void				resize_room_link(t_world *world, sfEvent *event)
{
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyNum1)
		world->room_radius += 0.01;
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyNum2)
		world->room_radius -= 0.01;
	if (world->room_radius < 0.05)
		world->room_radius = 0.05;
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyNum3)
		world->link_thick += 0.01;
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyNum4)
		world->link_thick -= 0.01;
	if (world->link_thick < 0.005)
		world->link_thick = 0.005;
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyNum5)
		world->interp += 10;
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyNum6)
		world->interp -= 10;
	if (world->interp < 10)
		world->interp = 10;
}

void				event_handle_2d(t_world *world, sfEvent *event)
{
	if (event->type == sfEvtClosed ||
		(event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape))
	{
		sfRenderWindow_close(world->win_2d);
		sfRenderWindow_close(world->win_3d);
	}
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEnter)
		g_lm_state |= LM_RESTART;
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeySpace)
		g_lm_state |= LM_STEP2;
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyP)
		g_lm_state = g_lm_state & LM_PATH ? g_lm_state & ~LM_PATH :
												g_lm_state | LM_PATH;
	resize_room_link(world, event);
}

static inline void	view_move(t_view *view, sfEvent *event)
{
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyW)
	{
		view->dx = -sin(view->angle_x / 180 * M_PI) * view->speed;
		view->dy = tan(view->angle_y / 180 * M_PI) * view->speed;
		view->dz = -cos(view->angle_x / 180 * M_PI) * view->speed;
	}
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyS)
	{
		view->dx = sin(view->angle_x / 180 * M_PI) * view->speed;
		view->dy = -tan(view->angle_y / 180 * M_PI) * view->speed;
		view->dz = cos(view->angle_x / 180 * M_PI) * view->speed;
	}
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyD)
	{
		view->dx = sin((view->angle_x + 90) / 180 * M_PI) * view->speed;
		view->dz = cos((view->angle_x + 90) / 180 * M_PI) * view->speed;
	}
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyA)
	{
		view->dx = sin((view->angle_x - 90) / 180 * M_PI) * view->speed;
		view->dz = cos((view->angle_x - 90) / 180 * M_PI) * view->speed;
	}
	view->x += view->dx;
	view->y += view->dy;
	view->z += view->dz;
}

void				event_handle_3d(t_world *world, sfEvent *event)
{
	if (event->type == sfEvtClosed ||
		(event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape))
		sfRenderWindow_close(world->win_3d);
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyM)
		g_lm_state = g_lm_state & LM_MOUS_TRAC ? g_lm_state & ~LM_MOUS_TRAC :
												g_lm_state | LM_MOUS_TRAC;
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyP)
		g_lm_state = g_lm_state & LM_PATH ? g_lm_state & ~LM_PATH :
												g_lm_state | LM_PATH;
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEnter)
		g_lm_state |= LM_RESTART3;
	if (g_lm_state & LM_MOUS_TRAC)
		view_move(world->view, event);
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeySpace)
		g_lm_state |= LM_STEP;
	resize_room_link(world, event);
}
