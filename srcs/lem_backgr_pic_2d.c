#include "lem_visual.h"

static inline int32_t	set_dp_sp(sfVector2i p0, sfVector2i p1, sfVector2i *dp,
																sfVector2i *sp)
{
	(*dp).x = abs(p1.x - p0.x);
	(*sp).x = p0.x < p1.x ? 1 : -1;
	(*dp).y = -abs(p1.y - p0.y);
	(*sp).y = p0.y < p1.y ? 1 : -1;
	return ((*dp).x + (*dp).y);
}

void					draw_link_2d(t_world *world, sfVector2i p0,
											sfVector2i p1, t_sfml_obj *proom)
{
	sfVector2i	dp;
	sfVector2i	sp;
	sfVector2f	pos;
	int32_t		err;
	int32_t		e2;

	err = set_dp_sp(p0, p1, &dp, &sp);
	while (1)
	{
		pos.x = (float)p0.x - world->link_thick;
		pos.y = (float)p0.y - world->link_thick;
		sfCircleShape_setPosition(proom->circle, pos);
		sfRenderTexture_drawCircleShape(world->rndr_texture, proom->circle, 0);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dp.y)
		{
			err += dp.y;
			p0.x += sp.x;
		}
		err += e2 <= dp.x ? dp.x : 0;
		p0.y += e2 <= dp.x ? sp.y : 0;
	}
}

int8_t					draw_room_2d(t_world *world, t_room *room_list,
											t_sfml_obj *proom, int32_t radius)
{
	int32_t		i;
	sfVector2f	pos;

	i = 0;
	print_info_2d(world);
	while (i < 3 * world->room_cnt)
	{
		pos.x = world->room_pixl_ar[i] - radius;
		pos.y = world->room_pixl_ar[i + 1] - radius;
		sfCircleShape_setPosition(proom->circle, pos);
		sfCircleShape_setFillColor(proom->circle,
							sfColor_fromInteger(world->room_pixl_ar[i + 2]));
		sfRenderTexture_drawCircleShape(world->rndr_texture, proom->circle, 0);
		sfText_setString(proom->text, room_list->name);
		pos.x += radius * 0.5;
		sfText_setPosition(proom->text, pos);
		sfRenderTexture_drawText(world->rndr_texture, proom->text, NULL);
		i += 3;
		room_list = room_list->next;
	}
	sfRenderTexture_display(world->rndr_texture);
	sfSprite_setTexture(world->rndr_sprite,
				sfRenderTexture_getTexture(world->rndr_texture), 0);
	return (1);
}
