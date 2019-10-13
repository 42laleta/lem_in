/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ant_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 05:06:33 by laleta            #+#    #+#             */
/*   Updated: 2019/10/10 05:53:26 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

void	set_ant_3d(t_world *world, float *pos)
{
	world->ant_pos = pos;
	render_3d(world);
	sfRenderWindow_display(world->win_3d);
	if (!(g_lm_state & LM_RESTART3))
		g_lm_state |= LM_STEP;
}

void	ant_line_3d(t_world *world, float *p0, float *p1)
{
	float		dp[world->ant_cnt * 3];
	float		p[world->ant_cnt * 3];
	int32_t		interp;
	int32_t		i;
	int32_t		j;

	interp = 200;
	i = 0;
	while (i < 3 * world->ant_cnt)
	{
		dp[i] = (p1[i] - p0[i]) / interp;
		dp[i + 1] = (p1[i + 1] - p0[i + 1]) / interp;
		dp[i + 2] = (p1[i + 2] - p0[i + 2]) / interp;
		i += 3;
	}
	i = 0;
	while (i < interp)
	{
		j = 0;
		while (j < 3 * world->ant_cnt)
		{
			p[j] = p0[j] + dp[j] * i;
			p[j + 1] = p0[j + 1] + dp[j + 1] * i;
			p[j + 2] = p0[j + 2] + dp[j + 2] * i;
			j += 3;
		}
		set_ant_3d(world, p);
		i++;
	}
}

void	ant_pos_3d(t_world *world)
{
	float		p0[world->ant_cnt * 3];
	float		p1[world->ant_cnt * 3];
	int32_t		i;
	uint32_t	room_id;
	t_step		*step_list;

	step_list = world->step_list;

	while (step_list->next)
	{
		i = 0;
		while (i < 3 * world->ant_cnt)
		{
			room_id = 6 * step_list->pos_ar[i / 3];
			p0[i] = world->room_norm_ar[room_id];
			p0[i + 1] = world->room_norm_ar[room_id + 1];
			p0[i + 2] = world->room_norm_ar[room_id + 2];
			room_id = 6 * step_list->next->pos_ar[i / 3];
			p1[i] = world->room_norm_ar[room_id];
			p1[i + 1] = world->room_norm_ar[room_id + 1];
			p1[i + 2] = world->room_norm_ar[room_id + 2];
			i += 3;
		}
		ant_line_3d(world, p0, p1);
		while ((g_lm_state & LM_STEP) &&
					sfRenderWindow_waitEvent(world->win_3d, world->event_3d))
		{
			if (world->event_3d->type == sfEvtKeyPressed &&
										world->event_3d->key.code == sfKeySpace)
			{
				g_lm_state &= ~LM_STEP;
				break;
			}
		}
		step_list = step_list->next;
	}
	g_lm_state |= LM_STOP_ANT3;
	g_lm_state &= ~LM_RESTART3;
	g_lm_state &= ~LM_STEP;

}
