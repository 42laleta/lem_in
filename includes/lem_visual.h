/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_visual.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 21:18:48 by laleta            #+#    #+#             */
/*   Updated: 2019/10/14 00:29:09 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_VISUAL_H
# define LEM_VISUAL_H

# include "libft.h"
# include <GL/glew.h>
# include "Graphics.h"
# include "OpenGL.h"
# include <errno.h>
# include <limits.h>
# include <sys/stat.h>
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <GLKit/GLKMatrix4.h>
# include "lem_shader.h"
# include "lem_loadfile.h"

# define LM_WIDTH		1200
# define LM_HEIGHT		1200
# define LM_WINPOS_X	100
# define LM_WINPOS_Y	100
# define L_NWIN_MIN		-1.0
# define L_NWIN_MAX		1.0
# define LM_MARGIN		200
# define LM_MARGIN_TX	30
# define L_PWIN_MIN		LM_MARGIN
# define L_PWIN_MAX		LM_WIDTH - LM_MARGIN
# define LM_START		"##start"
# define LM_END			"##end"
# define LM_ERROR		"ERROR"
# define LM_NAME_MAX	12
# define CL_START		1
# define CL_END			2
# define CL_DEFLT		4
# define BUFF_SZ		4096
# define LM_MOUS_TRAC	1
# define LM_TEXT_SHOW	2
# define LM_STOP_ANT	4
# define LM_RESTART		8
# define LM_STOP_ANT3	16
# define LM_RESTART3	32
# define LM_SECOND		64
# define LM_STEP		128
# define LM_STEP2		256

typedef struct		s_view
{
	float			x;
	float			y;
	float			z;
	float			dx;
	float			dy;
	float			dz;
	float			angle_x;
	float			angle_y;
	float			speed;
}					t_view;

typedef struct		s_room
{
	char			name[LM_NAME_MAX];
	int32_t			num;
	sfVector3f		coord;
	sfVector3f		color;
	struct s_room	*next;
}					t_room;

typedef struct		s_link
{
	sfVector2i		index;
	struct s_link	*next;
}					t_link;

typedef struct		s_step
{
	uint32_t		*pos_ar;
	struct s_step	*next;
}					t_step;

typedef struct		s_world
{
	sfVector2f		crd_max;
	sfVector2f		crd_min;
	int32_t			room_cnt;
	int32_t			link_cnt;
	int32_t			ant_cnt;
	uint32_t		step_cnt;
	uint32_t		start_room;
	sfRenderTexture	*rndr_texture;
	sfSprite		*rndr_sprite;
	sfRenderWindow	*win_3d;
	sfRenderWindow	*win_2d;
	sfEvent			*event_3d;
	sfEvent			*event_2d;
	float			*room_norm_ar;
	float			*ant_pos;
	uint32_t		*room_pixl_ar;
	uint32_t		*link_ar;
	GLuint			vbo_link;
	float			room_radius;
	float			link_thick;
	t_step			*step_list;
	t_view			*view;
	t_shader		*prog;
}					t_world;

typedef struct		s_pic_room
{
	sfCircleShape	*circle;
	sfText			*text;
	sfFont			*font;
}					t_pic_room;

extern uint16_t		g_lm_state;

void				init_null(t_world *world);
int8_t				init_world(t_world *world);
int8_t				init_gl(t_world *world);
void				init_glview(int32_t w, int32_t h, t_view *view);
void				destroy_world(t_world *world);
void				event_handle_3d(t_world *world, sfEvent *event);
void				event_handle_2d(t_world *world, sfEvent *event);
int8_t				parse_room(t_room **room_list, t_link **link_list,
																t_world *world);
int8_t				parse_link(t_room *room_list, t_link **link_list,
													t_world *world, char *s);
int8_t				parse_step(t_room *room_list, t_step **step_list,
																t_world *world);
t_room				*create_room(char *name, sfVector2i coord, int8_t color,
																t_world *world);
void				free_step_list(t_step **step_list);
void				free_room_list(t_room **room_list);
void				free_link_list(t_link **link_list);
void				free_world(t_world *world);
int8_t				gen_room_array(t_room *room_list, t_world *world,
																sfVector2i i);
int8_t				gen_link_array(t_link *link_list, t_world *world);
int8_t				gen_link_vertex(t_world *world);
int8_t				make_shader_prog(t_world *world);
int8_t				set_backgr_2d(t_world *world, t_room *room_list, int32_t i);
float				rand_minus_one_one(void);
float				rand_zero_one(void);
void				swap_ar(int32_t *ar);
int8_t				check_loadfile(char **argv);
void				render_2d(t_world *world);
void				render_3d(t_world *world);
void				ant_pos(t_world *world);
void				ant_pos_3d(t_world *world);
void				print_info_2d(t_world *world);
void				draw_link_2d(t_world *world, sfVector2i p1, sfVector2i p2,
															t_pic_room *proom);

#endif
