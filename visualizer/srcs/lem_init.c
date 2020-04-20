#include "lem_visual.h"

void				init_null(t_world *world)
{
	world->crd_max.x = INT_MIN;
	world->crd_max.y = INT_MIN;
	world->crd_min.x = INT_MAX;
	world->crd_min.y = INT_MAX;
	world->room_cnt = 0;
	world->link_cnt = 0;
	world->ant_cnt = 0;
	world->step_cnt = -1;
	world->start_room = 0;
	world->rndr_texture = NULL;
	world->rndr_sprite = NULL;
	world->win_2d = NULL;
	world->win_3d = NULL;
	world->room_norm_ar = NULL;
	world->room_pixl_ar = NULL;
	world->link_ar = NULL;
	world->vbo_link = 0;
	world->step_list = NULL;
	world->view = NULL;
	world->prog = NULL;
	world->room_radius = 0.1;
	world->link_thick = 4;
	world->interp = 200;
}

static inline void	init_view(t_world *world)
{
	sfVector2i			pos;

	world->view->x = 0.0;
	world->view->y = 0.5;
	world->view->z = 1.8;
	world->view->dx = 0.0;
	world->view->dy = 0.0;
	world->view->dz = 0.0;
	world->view->angle_x = 348.0;
	world->view->angle_y = -12.0;
	world->view->speed = 0.05;
	pos.x = 100;
	pos.y = 100;
	sfRenderWindow_setPosition(world->win_2d, pos);
	pos.x += LM_WIDTH;
	sfRenderWindow_setPosition(world->win_3d, pos);
}

int8_t				init_world(t_world *world)
{
	sfVideoMode			mode;
	sfContextSettings	settings;

	mode.width = LM_WIDTH;
	mode.height = LM_HEIGHT;
	mode.bitsPerPixel = 32;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 2;
	settings.majorVersion = 2;
	settings.minorVersion = 1;
	settings.attributeFlags = 0;
	if (!(world->win_3d = sfRenderWindow_create(mode, "LEM-IN-3D", sfClose |
		sfResize, &settings)) || !(world->win_2d = sfRenderWindow_create(mode,
		"LEM-IN-2D", sfClose, &settings)) ||
		!(world->view = (t_view*)malloc(sizeof(t_view))) ||
		!(world->prog = (t_shader*)malloc(sizeof(t_shader))) ||
		!(world->rndr_texture = sfRenderTexture_create(LM_WIDTH, LM_HEIGHT, 0))
	|| !(world->rndr_sprite = sfSprite_create()))
		return (0);
	init_view(world);
	return (1);
}

int8_t				init_gl(t_world *world)
{
	const float light0_pos[4] = {1, 1, 1, 0};

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	init_glview(LM_WIDTH, LM_HEIGHT, world->view);
	glewInit();
	if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader &&
													GL_EXT_geometry_shader4))
	{
		ft_printf(F_RED "%s" NONE, "OpenGL_shading_language(GLSL) disabled\n");
		return (0);
	}
	return (1);
}
