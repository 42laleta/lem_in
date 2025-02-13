NAME = visu
EXE_DIR = ../
EXE = $(EXE_DIR)$(NAME)
FLAGS = -Wall -Wextra -Werror
SOURCE = lem_main.c lem_parse_room.c lem_shader.c lem_util.c lem_data_array.c\
		lem_parse_link.c lem_render_2d.c lem_parse_step.c lem_ant_2d.c\
		lem_ant_3d.c lem_init.c lem_destroy.c lem_event.c lem_create_room.c\
		lem_shader_prog.c lem_render_3d.c lem_backgr_2d.c lem_backgr_txt_2d.c\
		lem_backgr_pic_2d.c lem_ant_set_3d.c lem_ant_set_2d.c
HEADER = lem_visual.h lem_shader.h lem_loadfile.h

INCLUDES = -Iincludes -I$(LIBFT_DIR)includes $(CSFML_INCLUDE) -I$(GLEW_DIR)/include

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ../libft/
CSFML_DIR = CSFML/
CSFML_INCLUDE = -I$(CSFML_DIR)include/SFML -I$(CSFML_DIR)include
GLEW_DIR = /usr/local/Cellar/glew/2.1.0_1/
VISU_DIR = visualizer/

LIB = -lft -framework OpenGL -framework GLUT -lm -lGLEW -framework AppKit\
		-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

LIB_DIR = -L$(LIBFT_DIR) -L$(CSFML_DIR)lib -L$(GLEW_DIR)lib
RPATH = -rpath,$(VISU_DIR)$(CSFML_DIR)lib/,-rpath,$(VISU_DIR)$(CSFML_DIR)Frameworks/

VPATH = srcs includes CSFML/lib CSFML/include/SFML

OBJ = $(SOURCE:.c=.o)
OBJ_DIR = obj/
OBJECT = $(patsubst %.o, $(OBJ_DIR)%.o, $(OBJ))

.PHONY : all clean fclean re

all : $(EXE)

$(EXE) : $(LIBFT) $(OBJECT)
	@echo "\033[1;3;34m"
	gcc $(FLAGS) $(OBJECT) -o $@ $(INCLUDES) $(LIB_DIR) -Wl,$(RPATH) $(LIB)
	@echo "\033[23;32m--[ "$(NAME) ]-- successfully compiled"\033[0m"

$(LIBFT) :
	@echo "\033[33;3m"
	@make -C $(LIBFT_DIR)
	@echo "\033[0m"

$(OBJ_DIR)%.o : %.c $(HEADER)
	@echo "\033[36;3m\c"
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[0m\c"

clean :
	@make -C $(LIBFT_DIR) clean
	@find $(OBJ_DIR) -type f -not -name '.gitkeep' -delete

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(EXE)

re : fclean all
