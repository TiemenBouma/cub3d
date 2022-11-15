#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"

void	hook_rotate_right(t_vars *vars, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vars->pov->dir_x;
	old_plane_x = vars->pov->plane_x;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->pov->dir_x = vars->pov->dir_x * cos(rotSpeed)
			- vars->pov->dir_y * sin(rotSpeed);
		vars->pov->dir_y = old_dir_x * sin(rotSpeed)
			+ vars->pov->dir_y * cos(rotSpeed);
		vars->pov->plane_x = vars->pov->plane_x * cos(rotSpeed)
			- vars->pov->plane_y * sin(rotSpeed);
		vars->pov->plane_y = old_plane_x * sin(rotSpeed)
			+ vars->pov->plane_y * cos(rotSpeed);
	}
}

void	hook_rotate_left(t_vars *vars, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vars->pov->dir_x;
	old_plane_x = vars->pov->plane_x;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->pov->dir_x = vars->pov->dir_x * cos(-rotSpeed)
			- vars->pov->dir_y * sin(-rotSpeed);
		vars->pov->dir_y = old_dir_x * sin(-rotSpeed)
			+ vars->pov->dir_y * cos(-rotSpeed);
		vars->pov->plane_x = vars->pov->plane_x * cos(-rotSpeed)
			- vars->pov->plane_y * sin(-rotSpeed);
		vars->pov->plane_y = old_plane_x * sin(-rotSpeed)
			+ vars->pov->plane_y * cos(-rotSpeed);
	}
}
