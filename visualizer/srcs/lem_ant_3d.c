#include "lem_visual.h"

static void				event_wait(t_world *world)
{
	while ((g_lm_state & LM_STEP) &&
					sfRenderWindow_waitEvent(world->win_3d, world->event_3d))
	{
		if (world->event_3d->type == sfEvtKeyPressed &&
										world->event_3d->key.code == sfKeySpace)
		{
			g_lm_state &= ~LM_STEP;
			break ;
		}
		if (world->event_3d->type == sfEvtKeyPressed &&
									world->event_3d->key.code == sfKeyEscape)
		{
			g_lm_state |= LM_EXIT;
			break ;
		}
	}
}

static inline void		set_p0_p1(float *p0, float *p1, t_world *world,
															t_step *step_list)
{
	int32_t		i;
	uint32_t	room_id;

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
}

void					ant_pos_3d(t_world *world)
{
	float		p0[world->ant_cnt * 3];
	float		p1[world->ant_cnt * 3];
	t_step		*step_list;

	step_list = world->step_list;
	while (!(g_lm_state & LM_EXIT) && step_list->next)
	{
		set_p0_p1(p0, p1, world, step_list);
		ant_line_3d(world, p0, p1);
		event_wait(world);
		step_list = step_list->next;
	}
	g_lm_state |= LM_STOP_ANT3;
	g_lm_state &= ~LM_RESTART3;
	g_lm_state &= ~LM_STEP;
	g_lm_state &= ~LM_EXIT;
}
