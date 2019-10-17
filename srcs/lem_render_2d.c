/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_render_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:16:24 by laleta            #+#    #+#             */
/*   Updated: 2019/10/14 06:31:33 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

static inline int8_t	init_pic_ant(t_sfml_obj *p_ant, t_world *world)
{
	if (!(p_ant->circle = sfCircleShape_create()) ||
		!(p_ant->sprite = sfSprite_create()) ||
		!(p_ant->texture = sfRenderTexture_create(LM_WIDTH, LM_HEIGHT, 0)))
		return (0);
	sfCircleShape_setRadius(p_ant->circle, world->room_radius * 100);
	sfCircleShape_setFillColor(p_ant->circle, sfBlue);
	return (1);
}

static inline void		destroy_pic_ant(t_sfml_obj *p_ant)
{
	if (p_ant)
	{
		if (p_ant->circle)
			sfCircleShape_destroy(p_ant->circle);
		if (p_ant->sprite)
			sfSprite_destroy(p_ant->sprite);
		if (p_ant->texture)
			sfRenderTexture_destroy(p_ant->texture);
	}
}

static void				event_wait(t_world *world)
{
	while ((g_lm_state & LM_STEP2) &&
					sfRenderWindow_waitEvent(world->win_2d, world->event_2d))
	{
		if (world->event_2d->type == sfEvtKeyPressed &&
										world->event_2d->key.code == sfKeySpace)
		{
			g_lm_state &= ~LM_STEP2;
			break;
		}
		if (world->event_2d->type == sfEvtKeyPressed && 
									world->event_2d->key.code == sfKeyEscape)
		{
			g_lm_state |= LM_EXIT;
			break;
		}
	}
}

static inline void		set_p0_p1(uint32_t *p0, uint32_t *p1, t_world *world,
															t_step *step_list)
{
	int32_t		i;
	uint32_t	room_id;

	i = 0;
	while (i < 2 * world->ant_cnt)
	{
		room_id = 3 * step_list->pos_ar[i / 2];
		p0[i] = world->room_pixl_ar[room_id];
		p0[i + 1] = world->room_pixl_ar[room_id + 1];
		room_id = 3 * step_list->next->pos_ar[i / 2];
		p1[i] = world->room_pixl_ar[room_id];
		p1[i + 1] = world->room_pixl_ar[room_id + 1];
		i += 2;
	}
}

int8_t					ant_pos_2d(t_world *world)
{
	uint32_t	p0[world->ant_cnt * 2];
	uint32_t	p1[world->ant_cnt * 2];
	t_step		*step_list;
	t_sfml_obj	p_ant;

	if (!init_pic_ant(&p_ant, world))
		return (0);
	step_list = world->step_list;
	while (!(g_lm_state & LM_EXIT) && step_list->next)
	{
		set_p0_p1(p0, p1, world, step_list);
		ant_line_2d(world, p0, p1, &p_ant);
		event_wait(world);
		step_list = step_list->next;
	}
	g_lm_state |= LM_STOP_ANT;
	g_lm_state &= ~LM_RESTART;
	g_lm_state &= ~LM_STEP2;
	g_lm_state &= ~LM_EXIT;
	destroy_pic_ant(&p_ant);
	return (1);
}
