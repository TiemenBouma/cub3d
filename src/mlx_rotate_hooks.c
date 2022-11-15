#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"

void	hook_rotate_left(t_vars *vars, double rotSpeed)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = vars->pov->dir_x;
		vars->pov->dir_x = vars->pov->dir_x * cos(rotSpeed) - vars->pov->dir_y * sin(rotSpeed);
		vars->pov->dir_y = oldDirX * sin(rotSpeed) + vars->pov->dir_y * cos(rotSpeed);
		double oldPlaneX = vars->pov->plane_x;
		vars->pov->plane_x = vars->pov->plane_x * cos(rotSpeed) - vars->pov->plane_y * sin(rotSpeed);
		vars->pov->plane_y = oldPlaneX * sin(rotSpeed) + vars->pov->plane_y * cos(rotSpeed);
	}
}

void	hook_rotate_right(t_vars *vars, double rotSpeed)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
    double oldDirX = vars->pov->dir_x;
    vars->pov->dir_x = vars->pov->dir_x * cos(-rotSpeed) - vars->pov->dir_y * sin(-rotSpeed);
    vars->pov->dir_y = oldDirX * sin(-rotSpeed) + vars->pov->dir_y * cos(-rotSpeed);
    double oldPlaneX = vars->pov->plane_x;
    vars->pov->plane_x = vars->pov->plane_x * cos(-rotSpeed) - vars->pov->plane_y * sin(-rotSpeed);
    vars->pov->plane_y = oldPlaneX * sin(-rotSpeed) + vars->pov->plane_y * cos(-rotSpeed);
	}
}