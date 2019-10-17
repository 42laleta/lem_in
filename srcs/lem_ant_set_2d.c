#include "lem_visual.h"

void				set_ant_2d(t_world *world, uint32_t *pos, t_sfml_obj *p_ant)
{
	sfVector2f		p;
	int32_t			i;

	i = 0;
	sfRenderTexture_drawSprite(p_ant->texture, world->rndr_sprite, 0);
	while (i < 2 * world->ant_cnt)
	{
		p.x = pos[i] - world->room_radius * 100;
		p.y = pos[i + 1] - world->room_radius * 100;
		sfCircleShape_setPosition(p_ant->circle, p);
		sfRenderTexture_drawCircleShape(p_ant->texture, p_ant->circle, NULL);
		i += 2;
	}
	sfRenderTexture_display(p_ant->texture);
	sfSprite_setTexture(p_ant->sprite,
								sfRenderTexture_getTexture(p_ant->texture), 0);
	sfRenderWindow_drawSprite(world->win_2d, p_ant->sprite, 0);
	sfRenderWindow_display(world->win_2d);
	if (!(g_lm_state & LM_RESTART))
		g_lm_state |= LM_STEP2;
}

void				render_2d(t_world *world)
{
	sfRenderWindow_pushGLStates(world->win_2d);
	if (!(g_lm_state & LM_STOP_ANT) || (g_lm_state & (LM_RESTART | LM_STEP2)))
		ant_pos_2d(world);
	sfRenderWindow_drawSprite(world->win_2d, world->rndr_sprite, 0);
	sfRenderWindow_display(world->win_2d);
	sfRenderWindow_popGLStates(world->win_2d);
}
