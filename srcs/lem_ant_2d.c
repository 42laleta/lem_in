/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_ant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 22:18:41 by laleta            #+#    #+#             */
/*   Updated: 2019/10/17 18:01:39 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

static inline void	set_dp_sp(t_line *ln, t_world *world)
{
	int32_t	i;

	i = 0;
	while (i < 2 * world->ant_cnt)
	{
		ln->dp[i] = abs((int32_t)ln->p1[i] - (int32_t)ln->p0[i]);
		ln->dp[i + 1] = -abs((int32_t)ln->p1[i + 1] - (int32_t)ln->p0[i + 1]);
		ln->sp[i] = ln->p0[i] < ln->p1[i] ? 1 : -1;
		ln->sp[i + 1] = ln->p0[i + 1] < ln->p1[i + 1] ? 1 : -1;
		ln->err[i] = ln->dp[i] + ln->dp[i + 1];
		i += 2;
	}
	ln->ant = 0;
}

static inline void	set_pos(t_line *ln, t_world *world)
{
	int32_t	i;

	i = 0;
	while (i < 2 * world->ant_cnt)
	{
		if (ln->p0[i] == ln->p1[i] && ln->p0[i + 1] == ln->p1[i + 1])
		{
			ln->ant_id[i / 2] = 1;
			i += 2;
			continue ;
		}
		ln->e2 = 2 * ln->err[i];
		if (ln->e2 >= ln->dp[i + 1])
		{
			ln->err[i] += ln->dp[i + 1];
			ln->p0[i] += ln->sp[i];
		}
		if (ln->e2 <= ln->dp[i])
		{
			ln->err[i] += ln->dp[i];
			ln->p0[i + 1] += ln->sp[i + 1];
		}
		i += 2;
	}
}

static void			event_poll(t_world *world)
{
	while (sfRenderWindow_pollEvent(world->win_2d, world->event_2d))
	{
		if (world->event_2d->type == sfEvtKeyPressed &&
									world->event_2d->key.code == sfKeyEscape)
			g_lm_state |= LM_EXIT;
	}
}

static inline void	set_ln(uint32_t *p0, uint32_t *p1, int32_t *dp, t_line *ln)
{
	ln->dp = dp;
	ln->p0 = p0;
	ln->p1 = p1;
}

void				ant_line_2d(t_world *world, uint32_t *p0, uint32_t *p1,
															t_sfml_obj *p_ant)
{
	int32_t		dp[world->ant_cnt * 2];
	int32_t		sp[world->ant_cnt * 2];
	int32_t		err[world->ant_cnt * 2];
	uint32_t	ant_id[world->ant_cnt];
	t_line		ln;

	set_ln(p0, p1, dp, &ln);
	ln.sp = sp;
	ln.sp = sp;
	ln.err = err;
	ln.ant_id = ant_id;
	set_dp_sp(&ln, world);
	while (!(g_lm_state & LM_EXIT) && ln.ant < world->ant_cnt)
	{
		set_ant_2d(world, ln.p0, p_ant);
		ln.i = 0;
		ln.ant = 0;
		while (ln.i < world->ant_cnt)
			ln.ant_id[ln.i++] = 0;
		set_pos(&ln, world);
		ln.i = 0;
		while (ln.i < world->ant_cnt)
			ln.ant += ln.ant_id[ln.i++];
		event_poll(world);
	}
}
