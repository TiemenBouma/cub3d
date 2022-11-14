#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"

void	init_cube_struct(t_cube *cube)
{
	cube->ceilling_rgb[0] = -1;
	cube->floor_rgb[0] = -1;
	cube->g_img_ceilling = NULL;
	cube->g_img_floor = NULL;
	cube->no = NULL;
	cube->ea = NULL;
	cube->so = NULL;
	cube->we = NULL;
	cube->texture_ea_wall = NULL;
	cube->texture_no_wall = NULL;
	cube->texture_so_wall = NULL;
	cube->texture_we_wall = NULL;
	cube->map = NULL;
	cube->map_length = 0;
	cube->map_width = 0;
	cube->window_x = SCREEN_X;
	cube->window_y = SCREEN_Y;
	cube->player_count = 0;
	cube->player_x = 0;
	cube->player_y = 0;
}

void	init_file_struct(t_file *file, char **argv)
{
	file->file_fd = 0;
	file->file_name = argv[1];
	file->start_line_map = 0;
}

void	init_pov_struct(t_pov *pov)
{
	pov->pos_x = 3;
	pov->pos_y = 3;
	pov->dir_x = 0;
	pov->dir_y = 1;
	pov->plane_x = 0.66;
	pov->plane_y = 0;

}

void	init_structs(t_vars *vars, char **argv)
{
	vars->gamecycle = 0;
	init_cube_struct(vars->cube);
	init_file_struct(vars->file, argv);
	init_pov_struct(vars->pov);
}
