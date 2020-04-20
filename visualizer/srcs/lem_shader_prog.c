#include "lem_visual.h"

int8_t	make_shader_prog(t_world *world)
{
	t_shader *prog;

	sfRenderWindow_setActive(world->win_3d, 1);
	prog = world->prog;
	if (!set_shader(&prog->prog_room, LM_SHAD_ROOM_V, NULL, LM_SHAD_ROOM_F) ||
		!set_shader(&prog->prog_link, LM_SHAD_LINK_V, LM_SHAD_LINK_G,
																LM_SHAD_LINK_F))
		return (0);
	prog->room_radius = glGetAttribLocation(prog->prog_room, "R");
	prog->link_width = glGetUniformLocation(prog->prog_link, "width");
	prog->viewport = glGetUniformLocation(prog->prog_room, "viewport");
	prog->coord_3d = glGetAttribLocation(prog->prog_link, "coord_3d");
	if (prog->room_radius == -1 || prog->viewport == -1 ||
		prog->coord_3d == -1 || prog->link_width == -1)
	{
		ft_printf(F_RED "Could not bind attribute\n" NONE);
		return (0);
	}
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	return (1);
}
