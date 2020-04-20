NAME = solve
EXE_DIR = ../
EXE = $(EXE_DIR)$(NAME)
FLAGS = -Wall -Wextra -Werror
SOURCE = n00_lem_in.c n01_init_game.c n02_lem_in_begin.c n04_lem_in_end.c\
		n100_dij.c n101_dij_processing.c n102_dij_queue.c n103_dij_queue_reset.c\
		n104_dij_after.c n105_dij_after_del.c n106_dij_pathfinder.c n10_debug.c\
		n11_debug_bfs.c n12_debug_dij.c n20_read.c n21_read_vertex.c\
		n22_read_vertex_final_set.c n23_read_edge.c n24_read_input.c\
		n30_path.c n50_ants_run.c n51_ants_run_move.c n60_bfs.c n70_backward_bfs.c\
		n71_backward_bfs_calc.c n72_backward_bfs_calc_backward.c\
		n73_backward_bfs_save_load.c n80_print_map.c
HEADER = lem_in.h

INCLUDES = -Iincludes -I$(LIBFT_DIR)includes

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ../libft/

LIB = -lft

LIB_DIR = -L$(LIBFT_DIR)

VPATH = srcs includes

OBJ = $(SOURCE:.c=.o)
OBJ_DIR = obj/
OBJECT = $(patsubst %.o, $(OBJ_DIR)%.o, $(OBJ))

.PHONY : all clean fclean re

all : $(EXE)

$(EXE) : $(LIBFT) $(OBJECT)
	@echo "\033[1;3;34m"
	gcc $(FLAGS) $(OBJECT) -o $@ $(INCLUDES) $(LIB_DIR) $(LIB)
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
