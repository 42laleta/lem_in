#include "lem_visual.h"

void					set_ant_3d(t_world *world, float *pos)
{
	world->ant_pos = pos;
	render_main_3d(world);
	sfRenderWindow_display(world->win_3d);
	if (!(g_lm_state & LM_RESTART3))
		g_lm_state |= LM_STEP;
}

static void				event_poll(t_world *world)
{
	while (sfRenderWindow_pollEvent(world->win_3d, world->event_3d))
	{
		if (world->event_3d->type == sfEvtKeyPressed && 
									world->event_3d->key.code == sfKeyEscape)
		g_lm_state |= LM_EXIT;
	}
}

static inline void		set_dp(float *p0, float *p1, float *dp, t_world *world)
{
	int32_t	i;

	i = 0;
	while (i < 3 * world->ant_cnt)
	{
		dp[i] = (p1[i] - p0[i]) / world->interp;
		dp[i + 1] = (p1[i + 1] - p0[i + 1]) / world->interp;
		dp[i + 2] = (p1[i + 2] - p0[i + 2]) / world->interp;
		i += 3;
	}
}

void					ant_line_3d(t_world *world, float *p0, float *p1)
{
	float		dp[world->ant_cnt * 3];
	float		p[world->ant_cnt * 3];
	int32_t		i;
	int32_t		j;

	set_dp(p0, p1, dp, world);
	i = 0;
	while (!(g_lm_state & LM_EXIT) && i < world->interp)
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
		event_poll(world);
		i++;
	}
}
