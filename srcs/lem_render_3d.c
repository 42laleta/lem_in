/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_render_3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 05:54:11 by laleta            #+#    #+#             */
/*   Updated: 2019/10/14 06:31:34 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

static void	render_link_3d(t_world *world)
{
	GLfloat	w;
	GLfloat	viewport[4];

	w = 0.014;
	glUseProgram(world->prog->prog_link);
	glGetFloatv(GL_VIEWPORT, viewport);
	glUniform4fv(world->prog->viewport, 1, viewport);
	glUniform1fv(world->prog->link_width, 1, &w);
    glBindBuffer(GL_ARRAY_BUFFER, world->vbo_link);
    glEnableVertexAttribArray(world->prog->coord_3d);
    glVertexAttribPointer(world->prog->coord_3d, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 3 * world->link_cnt);
    glDisableVertexAttribArray(world->prog->coord_3d);
	glUseProgram(0);
}

static void	render_ant_3d(t_world *world)
{
	int32_t	i;

	i = 0;
	while (i < 3 * world->ant_cnt)
	{
		glColor3f(0.1, 0.1, 1.0);
		glVertexAttrib1f(world->prog->room_radius, world->room_radius * 0.5);
		glVertex3f(world->ant_pos[i], world->ant_pos[i + 1],
														world->ant_pos[i + 2]);
		i += 3;
	}
}

static void	render_room_3d(t_world *world)
{
	int32_t	i;
	GLfloat	viewport[4];

	i = 0;
	glUseProgram(world->prog->prog_room);
	glGetFloatv(GL_VIEWPORT, viewport);
	glUniform4fv(world->prog->viewport, 1, viewport);
	glBegin(GL_POINTS);
	while (i < world->room_cnt * 6)
	{
		glColor3f(world->room_norm_ar[i + 3], world->room_norm_ar[i + 4],
													world->room_norm_ar[i + 5]);
		glVertexAttrib1f(world->prog->room_radius, world->room_radius);
		glVertex3f(world->room_norm_ar[i], world->room_norm_ar[i + 1],
													world->room_norm_ar[i + 2]);
		i += 6;
	}
	if (!(g_lm_state & LM_STOP_ANT3) || (g_lm_state & (LM_RESTART3|LM_STEP)))
		render_ant_3d(world);
	glEnd();
	glUseProgram(0);
}

void		render_main_3d(t_world *world)
{
	sfVector2i				pos_w;
	sfVector2i				pos_m;
	sfVector2i				pos;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	world->view->dx = 0;
	world->view->dy = 0;
	world->view->dz = 0;
	pos_m = sfMouse_getPositionRenderWindow(world->win_3d);
	pos_w = sfRenderWindow_getPosition(world->win_3d);
	pos.x = pos_w.x + LM_WIDTH / 2;
	pos.y = pos_w.y + LM_HEIGHT / 2;
	if (g_lm_state & LM_MOUS_TRAC)
	{
		world->view->angle_x = (pos.x - pos_m.x) / 4;
		world->view->angle_y = (pos.y - pos_m.y) / 4;
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(GLKMatrix4MakeLookAt(world->view->x, world->view->y,
	world->view->z, world->view->x - sin(world->view->angle_x / 180 * M_PI),
	world->view->y + tan(world->view->angle_y / 180 * M_PI),
	world->view->z - cos(world->view->angle_x / 180 * M_PI), 0, 1, 0).m);
	render_link_3d(world);
	render_room_3d(world);
}

void		render_3d(t_world *world)
{
	if (!(g_lm_state & LM_STOP_ANT3) || (g_lm_state & (LM_RESTART3 | LM_STEP)))
		ant_pos_3d(world);
	render_main_3d(world);
	sfRenderWindow_display(world->win_3d);
}
