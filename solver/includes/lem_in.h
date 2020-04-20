#ifndef LEM_IN_H
# define LEM_IN_H

# define JUST_NUM_PLACE 9

# define INPUT_ERR_GNL 1
# define INPUT_ERR_ANTS 2
# define INPUT_ERR_L 3
# define INPUT_ERR_SPLIT_NULL 4
# define INPUT_ERR_VERTEX 5
# define INPUT_ERR_EDGE 6
# define INPUT_ERR_CMD_FOR_EDGE 7
# define INPUT_ERR_NEW_ROOM 8
# define INPUT_ERR_NEW_LIST 9
# define INPUT_ERR_MSTACK 10
# define INPUT_ERR_COOR 11
# define INPUT_ERR_NUM_VERTEX 12
# define INPUT_ERR_NO_END_START 13
# define INPUT_ERR_MALLOC 14
# define INPUT_ERR_MIXUP 15
# define INPUT_ERR_VERTEX_NOT_FOUND 16
# define INPUT_ERR_EDGE_SAME_VERTEX 17
# define INPUT_ERR_MULI_START_OR_END 18
# define INPUT_ERR_END_PROCESS 19
# define INPUT_ERR_SAME_NAME_FOR_VERTEX 20
# define INPUT_ERR_SAME_EDGE 21

# define SHOW_CONN 3
# define SHOW_ROOM 7

# include "libft.h"
# include <limits.h>
# include <fcntl.h>

typedef	struct		s_room
{
	int				x;
	int				y;
	char			*name;

	int				idx;

	int				bfs_r_step;
	int				connect_to_end;

	int				ant;
	int				num_conn;

	int				path;
	int				hold_backward;
	int				best_path;
	int				best_hold_backward;

	t_list			*conn_dij;
	int				last_dij;
	int				pulled_dij;
	int				from_dij;
	int				val_dij;
	int				can_look;
	int				updated_dij;
	int				look_dij;
}					t_room;

typedef	struct		s_conn_dij
{
	t_room			*room;
	int				wgh;
	int				state;
}					t_conn_dij;

typedef	struct		s_path
{
	t_room			*from_end;
	int				len;
	int				trigger;
}					t_path;

typedef struct		s_ant_move
{
	int				ant;
	int				id_room;
}					t_ant_move;

typedef	struct		s_game
{
	t_room			**rooms;
	t_list			*lst_rooms;
	t_list			*out_or_error;

	int				start;
	int				end;
	int				ants;
	int				ant_in_run;
	int				num_vertex;
	int				path_lim;

	int				active_bfs;
	int				*bfs_1_queue;
	int				top_1_bfs;
	int				*bfs_2_queue;
	int				top_2_bfs;
	int				bfs_idx;
	int				bfs_level;
	int				backward_level;
	int				best_backward_level;
	int				best_result;

	t_room			**queue;
	int				idx_queue;

	t_path			**sol_path;
	int				idx_path;
	t_path			**best_sol_path;
	int				best_idx_path;

	t_ant_move		*move_line;
	t_ant_move		**move_sdw;
	int				idx_move;

	char			debug_error;
	char			debug_lst_room;
	char			debug_rooms;
	char			debug_game;
	char			debug_after_init;
	char			debug_next_bfs;
	char			debug_update_netword;
	char			debug_backward_find;
	char			debug_magic;
	char			debug_magic_stats;
	char			debug_magic_final;
	char			debug_levels;
	char			debug_real_bfs;
	char			debug_queue;
	char			debug_dij_all;
	char			debug_dij_decision;
	char			debug_dij_num_pull;
	char			debug_dij_after;

	char			free_edge_noupdate;
	char			dij_touch_noupdate;
	char			capacity_check;
	char			bfs_ants_run;
	char			no_unknows_cmd;
	char			space_end_line;
	char			queue_search;
	char			print_map;
	char			to_the_run;

	t_room			**dij_queue;
	int				idx_dij;
	int				dij_time;

}					t_game;

void				init_game(t_game *game);
int					get_fd(int argc, char *argv[]);

int					check_and_save_map(t_game *g, char *line, int rls);
int					save_gnl(t_game *g, char *line);
int					set_v_or_e(char *line, int *cmd, t_game *game);
int					set_command(char *line, int *cmd);
int					set_number(char *line, int *ants, short positiv);

int					input(t_game *game, int fd);
void				clean_out(t_game *g);
void				print_and_clean(t_game *g);

void				show_lst_room(t_game *game);
void				show_game(t_game *game);

void				init_room(t_room *room);
int					clean_words(char ***words, int idx, int error);
int					check_same_edge_conn(t_game *g, int node1, int node2);
int					set_vertex(char *line, int *cmd, t_game *game);
int					end_of_set_vetrex(t_game *game);
int					set_vetrix_for_edge(t_game *game);
int					set_edge(t_game *game, char *line);

int					set_path_lim(t_game *game);

int					init_search(t_game *g);
int					next_bfs(t_game *g);

void				ants_run(t_game *g);
void				ants_run_bfs(t_game *g);

void				show_rooms_conn(t_game *g);

void				update_end_conn(t_game *g, int bfs_step, int room_from);
void				update_conn(t_game *g, int bfs_step, int room_from,
					int room);
void				dfs_update_neg_end(t_game *g, int room, int room_from);
int					init_search(t_game *g);
int					check_for_end_bfs(t_game *g, int room);

void				show_bfs(t_game *g);
int					switch_bfs(t_game *g);
int					get_bfs(t_game *g);
void				add_next_bfs(t_game *g, int room);
int					init_bfs(t_game *g);
void				reset_bfs(t_game *g);

void				calc_backward(t_game *g);
void				show_room_path(t_game *g, int start);
void				show_sol_path(t_game *g);
void				show_stats(t_game *g);
void				show_stats_load(t_game *g);
int					calc_capacity(t_game *g);
int					calc_total_len(t_game *g);
int					virtual_ants_run(t_game *g);

void				move(t_game *g, int idx_path);

void				backward_bfs(t_game *g);
int					next_backward_bfs(t_game *g);
void				add_path_to_sol(t_game *g, int trg, int len);
void				reset_backward_bfs(t_game *g);

int					calc_trigger(t_game *g, int idx_sol_path);
int					calc_capacity(t_game *g);
int					calc_total_len(t_game *g);

void				save_best(t_game *g);
void				load_best_path(t_game *g);

int					read_input(t_game *g, int argc, char *argv[], int *fd);
int					check_and_malloc4sol(t_game *g);
void				debug_show(t_game *g);
int					start_search(t_game *g);
void				dinic_algo(t_game *g);
void				dinic_algo_pure(t_game *g);
void				debug_show_after(t_game *g);
int					check_exist_path(t_game *g);
void				map_and_ants_run(t_game *g);

int					real_bfs(t_game *g);
int					init_search_queue(t_game *g);
void				simpe_start_search(t_game *g);

int					init_bfs_queue(t_game *g);
void				push_bfs_queue(t_game *g, int add);
int					pull_bfs_queue(t_game *g);
void				reset_bfs_queue(t_game *g);
void				dinic_algo_queue(t_game *g);
void				apply_dfs(t_game *g, int room, int room_from);

int					check_same_edge_dij(t_game *g, int node1, int node2);
void				show_all_dij(t_game *g);
void				show_all_dij_list(t_game *g);
void				reset_dij_queue(t_game *g);
int					pull_dij_queue(t_game *g);
void				push_dij_queue(t_game *g, int add);
int					init_dij_queue(t_game *g);
void				print_dij_queue(t_game *g, char *begin_line);
void				push_simple_dij_queue(t_game *g, int add);
int					to_switch_room_dij(void *cur, void *back);
int					dij(t_game *g);
void				update_back_path(t_game *g);
void				update_rest_dij(t_game *g);
void				calc_backward_dij(t_game *g);
int					apply_dfs_backward(t_game *g, int room);
void				best_check(t_game *g, int *tmp);
void				debug_part(t_game *g, int tmp);
void				delete_dir_path(t_game *g, int trg, int before);
int					edge_delete(t_game *g, t_conn_dij *c_dij);
int					room_pulled(t_game *g, t_conn_dij *c_dij);
int					roomlook_n_edgenotfree(t_game *g, t_room *room,
					t_conn_dij *c_dij);
int					push_to_queue(t_game *g, t_room *room, t_conn_dij *c_dij);
int					just_update_value(t_game *g, t_room *room,
					t_conn_dij *c_dij);
int					suurballe(t_game *g);

#endif
