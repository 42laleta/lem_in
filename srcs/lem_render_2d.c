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
											sfVector2i p1, t_pic_room *proom)
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

void					set_logo(t_world *world)
{
	sfTexture	*texture;
	sfSprite	*sprite;
	sfVector2f	transf;

	texture = NULL;
	sprite = NULL;
	if (!(texture = sfTexture_createFromFile(LM_IMG, 0)) ||
		!(sprite = sfSprite_create()))
	{
		if (texture)
			sfTexture_destroy(texture);
		if (sprite)
			sfSprite_destroy(sprite);
		return ;
	}
	sfSprite_setTexture(sprite, texture, 0);
	transf.x = LM_MARGIN_TX;
	transf.y = LM_MARGIN_TX;
	sfSprite_setPosition(sprite, transf);
	transf.x = 0.05;
	transf.y = 0.05;
	sfSprite_setScale(sprite, transf);
	sfRenderTexture_drawSprite(world->rndr_texture, sprite, NULL);
	sfSprite_destroy(sprite);
	sfTexture_destroy(texture);
}

void					set_text(sfText *text, char *str, sfVector2f pos,
																	float size)
{
	sfText_setCharacterSize(text, size);
	sfText_setPosition(text, pos);
	sfText_setString(text, str);
}

static inline void		print_info_2d_aux(sfText *text, t_world *world)
{
	sfVector2f	pos;
	char		*str;

	pos.y += 180;
	pos.x = LM_MARGIN_TX;
	set_text(text, "room", pos, 30);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
	str = ft_itoa(world->room_cnt);
	pos.x += 90;
	set_text(text, str, pos, 30);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
	free(str);
	pos.y += 40;
	pos.x = LM_MARGIN_TX;
	set_text(text, "link", pos, 30);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
	str = ft_itoa(world->link_cnt);
	pos.x += 90;
	set_text(text, str, pos, 30);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
	free(str);
}

void					print_info_2d(t_world *world)
{
	sfVector2f	pos;
	sfFont		*font;
	sfText		*text;
	char		*str;

	if (!(font = sfFont_createFromFile(LM_FONT_INFO)) ||
		!(text = sfText_create()))
		return ;
	set_logo(world);
	sfText_setFillColor(text, sfColor_fromRGB(100, 100, 100));
	sfText_setFont(text, font);
	pos.x = LM_MARGIN_TX;
	pos.y = 140;
	set_text(text, "ant", pos, 30);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
	str = ft_itoa(world->ant_cnt);
	pos.x += 90;
	set_text(text, str, pos, 30);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
	free(str);
	print_info_2d_aux(text, world);
	sfText_destroy(text);
	sfFont_destroy(font);
}

void					render_2d(t_world *world)
{
	sfRenderWindow_pushGLStates(world->win_2d);
	if (!(g_lm_state & LM_STOP_ANT) || (g_lm_state & (LM_RESTART | LM_STEP2)))
		ant_pos(world);
	sfRenderWindow_drawSprite(world->win_2d, world->rndr_sprite, 0);
	sfRenderWindow_display(world->win_2d);
	sfRenderWindow_popGLStates(world->win_2d);
}
