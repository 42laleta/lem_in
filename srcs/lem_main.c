/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:18:22 by laleta            #+#    #+#             */
/*   Updated: 2019/10/17 18:06:05 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

uint16_t	g_lm_state = 0;

void	init_glview(int32_t w, int32_t h, t_view *view)
{
	float ratio;

	ratio = (1.0 * w) / (!h ? 1 : h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(GLKMatrix4MakePerspective(90, ratio, .1, 200).m);
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(GLKMatrix4MakeLookAt(view->x, view->y, view->z,
		view->x - sin(view->angle_x / 180 * M_PI),
		view->y + tan(view->angle_y / 180 * M_PI),
		view->z - cos(view->angle_x / 180 * M_PI), 0, 1, 0).m);
	glViewport(0, 0, w, h);
}

void	change_size(int32_t w, int32_t h)
{
	float	ratio;

	ratio = (1.0 * w) / (!h ? 1 : h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(GLKMatrix4MakePerspective(90, ratio, .1, 200).m);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

static inline int8_t	data_valid(int32_t argc, char **argv, t_world *world)
{
	(void)argc;
	srand(time(NULL));
	g_lm_state |= (LM_STOP_ANT | LM_STOP_ANT3);
	if (!(check_loadfile(argv)))
		return (0);
	init_null(world);
	if (!init_world(world) || !init_gl(world))
	{
		ft_printf(F_RED "%s: init error\n" NONE, argv[0]);
		destroy_world(world);
		return (0);
	}
	return (1);
}

int8_t					parse_map_gen_ar(t_world *world, t_room **room_list)
{
	t_step		*step_list;
	t_link		*link_list;
	sfVector2i	i;

	step_list = NULL;
	link_list = NULL;
	i.x = 0;
	i.y = 0;
	if (!parse_room(room_list, &link_list, world) ||
		!parse_step(*room_list, &step_list, world) ||
		!gen_room_array(*room_list, world, i) ||
		!gen_link_array(link_list, world) ||
		!gen_link_vertex(world))
	{
		if (link_list)
			free_link_list(&link_list);
		return (0);
	}
	world->room_radius = 1.0 / world->room_cnt;
	world->link_thick = 40 / world->room_cnt;
	world->step_list = step_list;
	free_link_list(&link_list);
	return (1);
}

void		render_loop(t_world *world)
{
	sfRenderWindow_setActive(world->win_3d, 1);
	change_size(LM_WIDTH, LM_HEIGHT);
	while (sfRenderWindow_pollEvent(world->win_3d, world->event_3d))
		event_handle_3d(world, world->event_3d);
	render_3d(world);
	sfRenderWindow_setActive(world->win_2d, 1);
	while (sfRenderWindow_pollEvent(world->win_2d, world->event_2d))
		event_handle_2d(world, world->event_2d);
	render_2d(world);
}

int32_t		main(int32_t argc, char **argv)
{
	sfEvent					event;
	sfEvent					event_2d;
	t_world					world;
	t_room					*room_list;

	room_list = NULL;
	if (!data_valid(argc, argv, &world))
		return (1);
	if (!parse_map_gen_ar(&world, &room_list) || !make_shader_prog(&world))
	{
		if (room_list)
			free_room_list(&room_list);
		destroy_world(&world);
		return (1);
	}
	world.event_3d = &event;
	world.event_2d = &event_2d;
	set_backgr_2d(&world, room_list, 0);
	free_room_list(&room_list);
	while (sfRenderWindow_isOpen(world.win_3d))
		render_loop(&world);
	destroy_world(&world);
	return (0);
}
