#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"

void	hook_move_up(t_vars *vars, double moveSpeed)
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	char	**map;

	pos_x = vars->pov->pos_x;
	pos_y = vars->pov->pos_y;
	dir_x = vars->pov->dir_x;
	dir_y = vars->pov->dir_y;
	map = vars->cube->map;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		if (map[(int)(pos_y + 0.1)][(int)(pos_x + dir_x * moveSpeed)] != '1'
			&& map[(int)(pos_y - 0.1)][(int)(pos_x + dir_x * moveSpeed)] != '1'
			&& map[(int)(pos_y)][(int)(pos_x + dir_x * moveSpeed + 0.1)] != '1'
			&& map[(int)(pos_y)][(int)(pos_x + dir_x * moveSpeed - 0.1)] != '1')
			pos_x += dir_x * moveSpeed;
		if (map[(int)(pos_y + dir_y * moveSpeed + 0.1)][(int)(pos_x)] != '1'
			&& map[(int)(pos_y + dir_y * moveSpeed - 0.1)][(int)(pos_x)] != '1'
			&& map[(int)(pos_y + dir_y * moveSpeed)][(int)(pos_x + 0.1)] != '1'
			&& map[(int)(pos_y + dir_y * moveSpeed)][(int)(pos_x - 0.1)] != '1')
			pos_y += dir_y * moveSpeed;
	}
}

void	hook_move_down(t_vars *vars, double moveSpeed)
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	char	**map;

	pos_x = vars->pov->pos_x;
	pos_y = vars->pov->pos_y;
	dir_x = vars->pov->dir_x;
	dir_y = vars->pov->dir_y;
	map = vars->cube->map;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		if (map[(int)(pos_y + 0.1)][(int)(pos_x - dir_x * moveSpeed)] != '1'
			&& map[(int)(pos_y - 0.1)][(int)(pos_x - dir_x * moveSpeed)] != '1'
			&& map[(int)(pos_y)][(int)(pos_x - dir_x * moveSpeed + 0.1)] != '1'
			&& map[(int)(pos_y)][(int)(pos_x - dir_x * moveSpeed - 0.1)] != '1')
			pos_x -= dir_x * moveSpeed;
		if (map[(int)(pos_y - dir_y * moveSpeed + 0.1)][(int)(pos_x)] != '1'
			&& map[(int)(pos_y - dir_y * moveSpeed - 0.1)][(int)(pos_x)] != '1'
			&& map[(int)(pos_y - dir_y * moveSpeed)][(int)(pos_x + 0.1)] != '1'
			&& map[(int)(pos_y - dir_y * moveSpeed)][(int)(pos_x - 0.1)] != '1')
			pos_y -= dir_y * moveSpeed;
	}
}

void	hook_move_left(t_vars *vars, double moveSpeed,
			double perpx, double perpy)
{
	double	pos_x;
	double	pos_y;
	char	**map;

	pos_x = vars->pov->pos_x;
	pos_y = vars->pov->pos_y;
	map = vars->cube->map;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		if (map[(int)(pos_y + 0.1)][(int)(pos_x + perpx * moveSpeed)] != '1'
			&& map[(int)(pos_y - 0.1)][(int)(pos_x + perpx * moveSpeed)] != '1'
			&& map[(int)(pos_y)][(int)(pos_x + perpx * moveSpeed + 0.1)] != '1'
			&& map[(int)(pos_y)][(int)(pos_x + perpx * moveSpeed - 0.1)] != '1')
			pos_x += perpx * moveSpeed;
		if (map[(int)(pos_y + perpy * moveSpeed + 0.1)][(int)(pos_x)] != '1'
			&& map[(int)(pos_y + perpy * moveSpeed - 0.1)][(int)(pos_x)] != '1'
			&& map[(int)(pos_y + perpy * moveSpeed)][(int)(pos_x + 0.1)] != '1'
			&& map[(int)(pos_y + perpy * moveSpeed)][(int)(pos_x - 0.1)] != '1')
			pos_y += perpy * moveSpeed;
	}
}

void	hook_move_right(t_vars *vars, double moveSpeed,
			double perpx, double perpy)
{
	double	pos_x;
	double	pos_y;
	char	**map;

	pos_x = vars->pov->pos_x;
	pos_y = vars->pov->pos_y;
	map = vars->cube->map;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		if (map[(int)(pos_y + 0.1)][(int)(pos_x - perpx * moveSpeed)] != '1'
			&& map[(int)(pos_y - 0.1)][(int)(pos_x - perpx * moveSpeed)] != '1'
			&& map[(int)(pos_y)][(int)(pos_x - perpx * moveSpeed + 0.1)] != '1'
			&& map[(int)(pos_y)][(int)(pos_x - perpx * moveSpeed - 0.1)] != '1')
			pos_x -= perpx * moveSpeed;
		if (map[(int)(pos_y - perpy * moveSpeed + 0.1)][(int)(pos_x)] != '1'
			&& map[(int)(pos_y - perpy * moveSpeed - 0.1)][(int)(pos_x)] != '1'
			&& map[(int)(pos_y - perpy * moveSpeed)][(int)(pos_x + 0.1)] != '1'
			&& map[(int)(pos_y - perpy * moveSpeed)][(int)(pos_x - 0.1)] != '1')
			pos_y -= perpy * moveSpeed;
	}
}
