#include "lem_visual.h"

int8_t					gen_link_array(t_link *link_list, t_world *world)
{
	int32_t	i;

	i = 0;
	if (!(world->link_ar = (uint32_t*)malloc(sizeof(uint32_t) *
														world->link_cnt * 2)))
		return (0);
	while (link_list)
	{
		world->link_ar[i++] = link_list->index.x;
		world->link_ar[i++] = link_list->index.y;
		link_list = link_list->next;
	}
	return (1);
}

static inline void		set_coef_offs(sfVector2f *c_norm, sfVector2f *c_pixl,
												sfVector2f *offset, t_world *w)
{
	(*offset).x = 0;
	(*offset).y = 0;
	if (w->crd_max.x == w->crd_min.x)
	{
		(*c_norm).x = 1;
		(*c_pixl).x = 1;
		(*offset).x = 0.5;
	}
	else
	{
		(*c_norm).x = (L_NWIN_MAX - L_NWIN_MIN) / (w->crd_max.x - w->crd_min.x);
		(*c_pixl).x = (L_PWIN_MAX - L_PWIN_MIN) / (w->crd_max.x - w->crd_min.x);
	}
	if (w->crd_max.y == w->crd_min.y)
	{
		(*c_norm).y = 1;
		(*c_pixl).y = 1;
		(*offset).y = 0.5;
	}
	else
	{
		(*c_norm).y = (L_NWIN_MAX - L_NWIN_MIN) / (w->crd_max.y - w->crd_min.y);
		(*c_pixl).y = (L_PWIN_MAX - L_PWIN_MIN) / (w->crd_max.y - w->crd_min.y);
	}
}

static inline int8_t	array_malloc(sfVector2f *coef_norm,
					sfVector2f *coef_pixl, sfVector2f *offset, t_world *world)
{
	if (!(world->room_pixl_ar = (uint32_t*)malloc(sizeof(uint32_t) *
														world->room_cnt * 3)) ||
		!(world->room_norm_ar = (float*)malloc(sizeof(float) *
														world->room_cnt * 6)))
		return (0);
	set_coef_offs(coef_norm, coef_pixl, offset, world);
	return (1);
}

int8_t					gen_room_array(t_room *room_list, t_world *world,
																sfVector2i i)
{
	sfVector2f	coef_norm;
	sfVector2f	coef_pixl;
	sfVector2f	offset;

	if (!array_malloc(&coef_norm, &coef_pixl, &offset, world))
		return (0);
	while (room_list)
	{
		world->room_norm_ar[i.x++] = (room_list->coord.x - world->crd_min.x +
										offset.x) * coef_norm.x + L_NWIN_MIN;
		world->room_norm_ar[i.x++] = (room_list->coord.y - world->crd_min.y +
										offset.y) * coef_norm.y + L_NWIN_MIN;
		world->room_norm_ar[i.x++] = room_list->coord.z;
		world->room_norm_ar[i.x++] = room_list->color.x;
		world->room_norm_ar[i.x++] = room_list->color.y;
		world->room_norm_ar[i.x++] = room_list->color.z;
		world->room_pixl_ar[i.y++] = (room_list->coord.x - world->crd_min.x +
								offset.x * 1000) * coef_pixl.x + L_PWIN_MIN;
		world->room_pixl_ar[i.y++] = (room_list->coord.y - world->crd_min.y +
								offset.y * 1000) * coef_pixl.y + L_PWIN_MIN;
		world->room_pixl_ar[i.y++] = sfColor_toInteger(sfColor_fromRGB(
room_list->color.x * 255, room_list->color.y * 255, room_list->color.z * 255));
		room_list = room_list->next;
	}
	return (1);
}

int8_t					gen_link_vertex(t_world *world)
{
	GLfloat		link_vertex[world->link_cnt * 3 * 3];
	int32_t		link;
	int32_t		room;
	int32_t		vert;
	int32_t		i;

	link = 0;
	vert = 0;
	i = 0;
	while (link < 2 * world->link_cnt)
	{
		room = 6 * world->link_ar[link];
		link_vertex[vert] = world->room_norm_ar[room];
		link_vertex[vert + 1] = world->room_norm_ar[room + 1];
		link_vertex[vert + 2] = world->room_norm_ar[room + 2];
		if (++i % 3 != 0)
			link++;
		vert += 3;
	}
	glGenBuffers(1, &(world->vbo_link));
	glBindBuffer(GL_ARRAY_BUFFER, world->vbo_link);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * world->link_cnt * 3 * 3,
												link_vertex, GL_STATIC_DRAW);
	i = (glGetError() != GL_NO_ERROR) ? 0 : 1;
	return (i);
}
