/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_loadfile.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:05:43 by laleta            #+#    #+#             */
/*   Updated: 2019/10/14 02:20:43 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_LOADFILE_H
# define LEM_LOADFILE_H

static char *g_lem_loadfile[] =
{
	"resources/font/hand.otf",
	"resources/font/l_eyes.ttf",
	"resources/font/square.ttf",
	"resources/img/ant.png",
	""
};

# define LM_FONT_ROOM	g_lem_loadfile[0]
# define LM_FONT_TITLE	g_lem_loadfile[1]
# define LM_FONT_INFO	g_lem_loadfile[2]
# define LM_IMG			g_lem_loadfile[3]

#endif
