/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_backgr_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:13:18 by laleta            #+#    #+#             */
/*   Updated: 2019/10/14 02:16:40 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

static int8_t	init_pic_room(t_sfml_obj *proom, t_world *world)
{
	if (!(proom->circle = sfCircleShape_create()) ||
		!(proom->text = sfText_create()) ||
		!(proom->font = sfFont_createFromFile(LM_FONT_ROOM)))
		return (0);
	sfCircleShape_setRadius(proom->circle, world->link_thick);
	sfCircleShape_setFillColor(proom->circle, sfColor_fromRGB(204, 204, 204));
	sfText_setFont(proom->text, proom->font);
	sfText_setCharacterSize(proom->text, world->room_radius * 680);
	sfText_setFillColor(proom->text, sfBlack);
	sfText_setOutlineColor(proom->text, sfWhite);
	sfText_setOutlineThickness(proom->text, 1);
	return (1);
}

static void		destroy_pic_room(t_sfml_obj *proom)
{
	if (proom)
	{
		if (proom->circle)
			sfCircleShape_destroy(proom->circle);
		if (proom->text)
			sfText_destroy(proom->text);
		if (proom->font)
			sfFont_destroy(proom->font);
	}
}

int8_t			set_backgr_2d(t_world *world, t_room *room_list, int32_t i)
{
	uint32_t	r1;
	uint32_t	r2;
	sfVector2i	p1;
	sfVector2i	p2;
	t_sfml_obj	proom;

	if (!init_pic_room(&proom, world))
		return (0);
	sfRenderTexture_clear(world->rndr_texture, sfBlack);
	while (i < 2 * world->link_cnt)
	{
		r1 = 3 * world->link_ar[i];
		r2 = 3 * world->link_ar[i + 1];
		p1.x = world->room_pixl_ar[r1];
		p1.y = world->room_pixl_ar[r1 + 1];
		p2.x = world->room_pixl_ar[r2];
		p2.y = world->room_pixl_ar[r2 + 1];
		draw_link_2d(world, p1, p2, &proom);
		i += 2;
	}
	sfCircleShape_setRadius(proom.circle, world->room_radius * 400);
	draw_room_2d(world, room_list, &proom, world->room_radius * 400);
	destroy_pic_room(&proom);
	return (1);
}
