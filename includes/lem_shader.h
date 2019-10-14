/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_shader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 02:14:28 by laleta            #+#    #+#             */
/*   Updated: 2019/10/14 02:14:32 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_SHADER_H
# define LEM_SHADER_H

# include "lem_visual.h"

# define LM_SHAD_ROOM_V	"shaders/sphere_vert.glsl"
# define LM_SHAD_ROOM_F	"shaders/sphere_frag.glsl"
# define LM_SHAD_LINK_V	"shaders/cylinder_vert.glsl"
# define LM_SHAD_LINK_G	"shaders/cylinder_geom.glsl"
# define LM_SHAD_LINK_F	"shaders/cylinder_frag.glsl"

typedef	struct	s_shader
{
	GLuint		prog_room;
	GLuint		prog_link;
	GLint		viewport;
	GLint		room_radius;
	GLint		link_width;
	GLint		coord_3d;
}				t_shader;

int8_t			read_compile_shader(const char *filename, GLuint *hdlr,
																GLenum type);
int8_t			set_shader(GLuint *prog, const char *vs, const char *gs,
																const char *fs);

#endif
