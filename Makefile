# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laleta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/07 19:28:58 by laleta            #+#    #+#              #
#    Updated: 2019/10/13 20:41:44 by laleta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visu_hex
FLAGS = -g -Wall -Wextra -Werror
SOURCE = lem_main.c lem_parse_room.c lem_shader.c lem_util.c lem_data_array.c\
		lem_parse_link.c lem_render_2d.c lem_parse_step.c lem_ant_2d.c\
		lem_ant_3d.c lem_init.c lem_destroy.c lem_event.c lem_create_room.c\
		lem_shader_prog.c lem_render_3d.c lem_backgr_2d.c lem_backgr_txt_2d.c\
		lem_backgr_pic_2d.c lem_ant_set_3d.c lem_ant_set_2d.c
HEADER = lem_visual.h lem_shader.h lem_loadfile.h

INCLUDES = -Iincludes -I$(LIBFT_DIR)includes $(CSFML_INCLUDE) -I$(GLEW_DIR)/include

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libft/
CSFML_DIR = CSFML/
CSFML_INCLUDE = -I$(CSFML_DIR)include/SFML -I$(CSFML_DIR)include
GLEW_DIR = /Users/laleta/.brew/Cellar/glew/2.1.0/

LIB = -lft -framework OpenGL -framework GLUT -lm -lGLEW -framework AppKit\
		-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

LIB_DIR = -L$(LIBFT_DIR) -L$(CSFML_DIR)lib -L$(GLEW_DIR)lib
RPATH = -rpath,$(CSFML_DIR)lib/,-rpath,$(CSFML_DIR)Frameworks/

VPATH = srcs includes CSFML/lib CSFML/include/SFML

OBJECT = $(SOURCE:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJECT)
	@echo "\033[1;3;34m"
	gcc $(FLAGS) $(OBJECT) -o $@ $(INCLUDES) $(LIB_DIR) -Wl,$(RPATH) $(LIB)
	@echo "\033[23;32m--[ "$(NAME) ]-- successfully compiled"\033[0m"

$(LIBFT) :
	@echo "\033[33;3m"
	@make -C $(LIBFT_DIR)
	@echo "\033[0m"

%.o : %.c $(HEADER)
	@echo "\033[36;3m"
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[0m"

clean :
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJECT)

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re : fclean all
