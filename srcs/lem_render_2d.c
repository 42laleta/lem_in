/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_render_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:16:24 by laleta            #+#    #+#             */
/*   Updated: 2019/10/13 22:28:10 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

int8_t	draw_link_2d(t_world *world, sfVector2i p1, sfVector2i p2, float t)
{
	sfVector2i	dp;
	sfVector2i	sp;
	int			err;
	int			e2;
	int			x2;
	int			y2;
	float		ed;
	sfImage		*image;
	sfTexture	*texture;

	if (!(image = sfImage_createFromColor(LM_WIDTH, LM_HEIGHT, sfTransparent))) 
		return (0);
	dp.x = abs(p2.x - p1.x);
	sp.x = p1.x < p2.x ? 1 : -1;
	dp.y = abs(p2.y - p1.y);
	sp.y = p1.y < p2.y ? 1 : -1;
	err = dp.x - dp.y;
	ed = dp.x + dp.y == 0 ? 1 : sqrt((float)dp.x * dp.x + (float)dp.y * dp.y);
	t = (t + 1) / 2;
	while (1)
	{
		sfImage_setPixel(image, (uint32_t)p1.x, (uint32_t)p1.y,
		sfColor_fromRGBA(204, 204, 204, 255 -
							fmax(0, 255 * (abs(err - dp.x + dp.y) / ed - t + 1))));
		e2 = err;
		x2 = p1.x;
		if (2 * e2 >= -dp.x)
		{
			e2 += dp.y;
			y2 = p1.y;
			while (e2 < ed * t && (p2.y != y2 || dp.x > dp.y))
			{
				sfImage_setPixel(image, (uint32_t)p1.x, (uint32_t)(y2 += sp.y),
				sfColor_fromRGBA(204, 204, 204, 255 -
										fmax(0, 255 * (abs(e2) / ed - t + 1))));
				e2 += dp.x;
			}
			if (p1.x == p2.x)
				break;
			e2 = err;
			err -= dp.y;
			p1.x += sp.x;
		}
		if (2 * e2 <= dp.y)
		{
			e2 = dp.x - e2;
			while (e2 < ed * t && (p2.x != x2 || dp.x < dp.y))
			{
				sfImage_setPixel(image, (uint32_t)(x2 += sp.x), (uint32_t)p1.y,
				sfColor_fromRGBA(204, 204, 204, 255 -
										fmax(0, 255 * (abs(e2) / ed - t + 1))));
				e2 += dp.y;
			}
			if (p1.y == p2.y)
				break;
			err += dp.x;
			p1.y += sp.y;
		}
	}
	if (!(texture = sfTexture_createFromImage(image, NULL)))
		return (0);
	sfSprite_setTexture(world->rndr_sprite, texture, 0);
	sfRenderTexture_drawSprite(world->rndr_texture, world->rndr_sprite, 0);
	sfTexture_destroy(texture);
	sfImage_destroy(image);
	return (1);
}

void	set_text(sfText *text, char *str, sfVector2f pos, float size)
{
	sfText_setCharacterSize(text, size);
	sfText_setPosition(text, pos);
	sfText_setString(text, str);
}

void	print_info_2d(t_world *world)
{
	sfVector2f	pos;
	sfFont		*font_title;
	sfFont		*font_info;
	sfText		*text;
	char		*str;
sfTexture	*texture;
sfSprite	*sprite;
sfVector2f	scale;

	if (!(font_title = sfFont_createFromFile(LM_FONT_TITLE)) ||
		!(font_info = sfFont_createFromFile(LM_FONT_INFO)) ||
		!(text = sfText_create()))
		return ;
pos.x = LM_MARGIN_TX;
pos.y = LM_MARGIN_TX;
scale.x = 0.05;
scale.y = 0.05;
texture = sfTexture_createFromFile("resources/img/ant.png", 0);
sprite = sfSprite_create();
sfSprite_setTexture(sprite, texture,0);
sfSprite_setScale(sprite, scale);
sfSprite_setPosition(sprite, pos);
sfRenderTexture_drawSprite(world->rndr_texture, sprite, NULL);
	sfText_setFont(text, font_title);
	sfText_setFillColor(text, sfColor_fromRGB(100, 100, 100));
	pos.x = LM_MARGIN_TX;
	pos.y = 0;
	sfText_setFont(text, font_info);
	pos.y += 140;
	set_text(text, "ant", pos, 30);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
	str = ft_itoa(world->ant_cnt);
	pos.x += 90;
	set_text(text, str, pos, 30);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
	free(str);
	pos.y += 40;
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
	sfText_destroy(text);
	sfFont_destroy(font_title);
	sfFont_destroy(font_info);
sfTexture_destroy(texture);
sfSprite_destroy(sprite);
}

void	render_2d(t_world *world)
{
	sfRenderWindow_pushGLStates(world->win_2d);
	if (!(g_lm_state & LM_STOP_ANT) || (g_lm_state & (LM_RESTART | LM_STEP2)))
		ant_pos(world);
	sfRenderWindow_drawSprite(world->win_2d, world->rndr_sprite, 0);
	sfRenderWindow_display(world->win_2d);
	sfRenderWindow_popGLStates(world->win_2d);
}
