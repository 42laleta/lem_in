#include "lem_visual.h"

static void				set_logo(t_world *world)
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

static inline void		set_text(sfText *text, char *str, sfVector2f pos,
																	float size)
{
	sfText_setCharacterSize(text, size);
	sfText_setPosition(text, pos);
	sfText_setString(text, str);
}

static inline void		print_info_2d_txt1(sfText *text, t_world *world)
{
	sfVector2f	pos;
	char		*str;

	pos.x = LM_MARGIN_TX;
	pos.y = 140;
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
}

static inline void		print_info_2d_txt2(sfText *text, t_world *world)
{
	sfVector2f	pos;
	char		*str;

	pos.y = 220;
	pos.x = LM_MARGIN_TX;
	set_text(text, "link", pos, 30);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
	str = ft_itoa(world->link_cnt);
	pos.x += 90;
	set_text(text, str, pos, 30);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
	free(str);
	pos.x = LM_MARGIN_TX;
	pos.y = LM_HEIGHT - 50;
	set_text(text, "[SPACE] step      [ENTER] gogogo      [M] 3d-move on/off\
			[A S D W] 3d-control      [ESC] stop/exit", pos, 20);
	sfRenderTexture_drawText(world->rndr_texture, text, NULL);
}

void					print_info_2d(t_world *world)
{
	sfFont		*font;
	sfText		*text;

	font = NULL;
	text = NULL;
	if (!(font = sfFont_createFromFile(LM_FONT_INFO)) ||
		!(text = sfText_create()))
	{
		if (text)
			sfText_destroy(text);
		if (font)
			sfFont_destroy(font);
		return ;
	}
	set_logo(world);
	sfText_setFillColor(text, sfColor_fromRGB(100, 100, 100));
	sfText_setFont(text, font);
	print_info_2d_txt1(text, world);
	print_info_2d_txt2(text, world);
	sfText_destroy(text);
	sfFont_destroy(font);
}
