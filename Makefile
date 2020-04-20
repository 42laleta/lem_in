EXE1_DIR = solver
EXE2_DIR = visualizer

.PHONY : all clean fclean re

all :
	@make -C $(EXE1_DIR)
	@make -C $(EXE2_DIR)

clean :
	@make -C $(EXE1_DIR) clean
	@make -C $(EXE2_DIR) clean

fclean : clean
	@make -C $(EXE1_DIR) fclean
	@make -C $(EXE2_DIR) fclean

re : fclean all
