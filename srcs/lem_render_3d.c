/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_render_3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 05:54:11 by laleta            #+#    #+#             */
/*   Updated: 2019/10/10 05:54:14 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_visual.h"

void	render_3d(t_world *world)
{
	sfVector2i				pos_w;
	sfVector2i				pos_m;
	int						xt;
	int						yt;
	t_view					*view;	
	
	view = world->view;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

if (!(g_lm_state & LM_MOUS_TRAC) || !(g_lm_state & LM_SECOND))
{
	view->dx = 0;
	view->dy = 0;
	view->dz = 0;
	pos_m = sfMouse_getPositionRenderWindow(world->win_3d);
	pos_w = sfRenderWindow_getPosition(world->win_3d);
	xt = pos_w.x + LM_WIDTH / 2;
	yt = pos_w.y + LM_HEIGHT / 2;
	if (g_lm_state & LM_SECOND)
	{
		view->angle_x = (xt - pos_m.x) / 4;
		view->angle_y = (yt - pos_m.y) / 4;
	}
	g_lm_state |= LM_SECOND;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(GLKMatrix4MakeLookAt(view->x, view->y, view->z,
		view->x - sin(view->angle_x / 180 * M_PI),
		view->y + tan(view->angle_y / 180 * M_PI),
		view->z - cos(view->angle_x / 180 * M_PI), 0, 1, 0).m);
}
	glUseProgram(world->prog->prog_link);
	GLfloat viewport[4];
	glGetFloatv(GL_VIEWPORT, viewport);
	glUniform4fv(world->prog->viewport, 1, viewport);
GLfloat w = 0.014;
	glUniform1fv(world->prog->link_width, 1, &w);//orld->link_thick);
    glBindBuffer(GL_ARRAY_BUFFER, world->vbo_link);
    glEnableVertexAttribArray(world->prog->coord_3d);
    glVertexAttribPointer(world->prog->coord_3d, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 3 * world->link_cnt);
    glDisableVertexAttribArray(world->prog->coord_3d);
	glUseProgram(0);

	glUseProgram(world->prog->prog_room);
	glGetFloatv(GL_VIEWPORT, viewport);
	glUniform4fv(world->prog->viewport, 1, viewport);
	int32_t i = 0;
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
	{
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
	glEnd();
	glUseProgram(0);
}
