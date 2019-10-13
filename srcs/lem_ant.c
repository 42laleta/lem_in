/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 22:18:41 by laleta            #+#    #+#             */
/*   Updated: 2019/10/10 05:53:37 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

void	set_ant(t_world *world, uint32_t *pos)
{
	sfCircleShape	*circle;
	sfVector2f		p;
	int32_t			i;
	sfRenderTexture	*texture;
	sfSprite		*sprite;

	i = 0;
	texture = sfRenderTexture_create(LM_WIDTH, LM_HEIGHT, 0);
	sprite = sfSprite_create();
	sfRenderTexture_drawSprite(texture, world->rndr_sprite, 0);
	circle = sfCircleShape_create();
	sfCircleShape_setRadius(circle, world->room_radius * 100);
	sfCircleShape_setFillColor(circle, sfBlue);
	while (i < 2 * world->ant_cnt)
	{
		p.x = pos[i] - world->room_radius * 100;
		p.y = pos[i + 1] - world->room_radius * 100;
		sfCircleShape_setPosition(circle, p);
		sfRenderTexture_drawCircleShape(texture, circle, NULL);
		i += 2;
	}
	sfRenderTexture_display(texture);
	sfSprite_setTexture(sprite, sfRenderTexture_getTexture(texture), 0);
	sfRenderWindow_drawSprite(world->win_2d, sprite, 0);
	sfRenderWindow_display(world->win_2d);
	sfCircleShape_destroy(circle);
	sfRenderTexture_destroy(texture);
	sfSprite_destroy(sprite);
	if (!(g_lm_state & LM_RESTART))
		g_lm_state |= LM_STEP2;
}

void	ant_line(t_world *world, uint32_t *p0, uint32_t *p1)
{
	int32_t		*dp;
	int32_t		*sp;
	int32_t		*err;
	int32_t		e2;
	int32_t		i;
	int32_t		ant;
	uint8_t		ant_id[world->ant_cnt];

	if (!(dp = (int32_t*)malloc(sizeof(int32_t) * world->ant_cnt * 2)) ||
		!(sp = (int32_t*)malloc(sizeof(int32_t) * world->ant_cnt * 2)) ||
		!(err = (int32_t*)malloc(sizeof(int32_t) * world->ant_cnt * 2)))
		return ;

	ant = 0;
	i = 0;
	while (i < 2 * world->ant_cnt)
	{
		dp[i] = abs((int32_t)p1[i] - (int32_t)p0[i]);
		dp[i + 1] = -abs((int32_t)p1[i + 1] - (int32_t)p0[i + 1]);
		sp[i] = p0[i] < p1[i] ? 1 : -1;
		sp[i + 1] = p0[i + 1] < p1[i + 1] ? 1 : -1;
		err[i] = dp[i] + dp[i + 1];
		i += 2;
	}
	while (ant < world->ant_cnt)
	{
		set_ant(world, p0);
		i = 0;
		ant = 0;
		while (i < world->ant_cnt)
			ant_id[i++] = 0;
		i = 0;
		while (i < 2 * world->ant_cnt)
		{
			if (p0[i] == p1[i] && p0[i + 1] == p1[i + 1])
			{
				ant_id[i / 2] = 1; 
				i += 2;
				continue ;
			}
			e2 = 2 * err[i];
			if (e2 >= dp[i + 1])
			{
				err[i] += dp[i + 1];
				p0[i] += sp[i];
			}
			if (e2 <= dp[i])
			{
				err[i] += dp[i];
				p0[i + 1] += sp[i + 1];
			}
			i += 2;
		}
	i = 0;
	while (i < world->ant_cnt)
		ant += ant_id[i++];
	}
	free(dp);
	free(sp);
	free(err);
}

void	ant_pos(t_world *world)
{
	uint32_t	*p0;
	uint32_t	*p1;
	int32_t		i;
	uint32_t	room_id;
	t_step		*step_list;

	step_list = world->step_list;

	p0 = (uint32_t*)malloc(sizeof(uint32_t) * world->ant_cnt * 2);
	p1 = (uint32_t*)malloc(sizeof(uint32_t) * world->ant_cnt * 2);
	while (step_list->next)
	{
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
		ant_line(world, p0, p1);
		while ((g_lm_state & LM_STEP2) &&
					sfRenderWindow_waitEvent(world->win_2d, world->event_2d))
		{
			if (world->event_2d->type == sfEvtKeyPressed &&
										world->event_2d->key.code == sfKeySpace)
			{
				g_lm_state &= ~LM_STEP2;
				break;
			}
		}
		step_list = step_list->next;
	}
	g_lm_state |= LM_STOP_ANT;
	g_lm_state &= ~LM_RESTART;
	g_lm_state &= ~LM_STEP2;
	free(p0);
	free(p1);
}
