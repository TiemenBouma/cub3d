#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"

void	hook_move_up(t_vars *vars, double moveSpeed)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
	{
		if(vars->cube->map[(int)(vars->pov->pos_y + 0.1)][(int)(vars->pov->pos_x + vars->pov->dir_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - 0.1)][(int)(vars->pov->pos_x + vars->pov->dir_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x + vars->pov->dir_x * moveSpeed + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x + vars->pov->dir_x * moveSpeed - 0.1)] != '1') 
			vars->pov->pos_x += vars->pov->dir_x * moveSpeed;
		if(vars->cube->map[(int)(vars->pov->pos_y + vars->pov->dir_y * moveSpeed + 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y + vars->pov->dir_y * moveSpeed - 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y + vars->pov->dir_y * moveSpeed)][(int)(vars->pov->pos_x + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y + vars->pov->dir_y * moveSpeed)][(int)(vars->pov->pos_x - 0.1)] != '1') 
			vars->pov->pos_y += vars->pov->dir_y * moveSpeed;
		else
		{
			printf("hit wall\n");
		}
	}
}

void	hook_move_down(t_vars *vars, double moveSpeed)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		if(vars->cube->map[(int)(vars->pov->pos_y + 0.1)][(int)(vars->pov->pos_x - vars->pov->dir_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - 0.1)][(int)(vars->pov->pos_x - vars->pov->dir_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x - vars->pov->dir_x * moveSpeed + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x - vars->pov->dir_x * moveSpeed - 0.1)] != '1') 
			vars->pov->pos_x -= vars->pov->dir_x * moveSpeed;
		if(vars->cube->map[(int)(vars->pov->pos_y - vars->pov->dir_y * moveSpeed + 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - vars->pov->dir_y * moveSpeed - 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - vars->pov->dir_y * moveSpeed)][(int)(vars->pov->pos_x + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - vars->pov->dir_y * moveSpeed)][(int)(vars->pov->pos_x - 0.1)] != '1') 
			vars->pov->pos_y -= vars->pov->dir_y * moveSpeed;
		else
		{
			printf("hit wall\n");
		}
	}
}

void	hook_move_left(t_vars *vars, double moveSpeed, double dir_perp_x, double dir_perp_y)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		if(vars->cube->map[(int)(vars->pov->pos_y + 0.1)][(int)(vars->pov->pos_x + dir_perp_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - 0.1)][(int)(vars->pov->pos_x + dir_perp_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x + dir_perp_x * moveSpeed + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x + dir_perp_x * moveSpeed - 0.1)] != '1') 
			vars->pov->pos_x += dir_perp_x * moveSpeed;
		if(vars->cube->map[(int)(vars->pov->pos_y + dir_perp_y * moveSpeed + 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y + dir_perp_y * moveSpeed - 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y + dir_perp_y * moveSpeed)][(int)(vars->pov->pos_x + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y + dir_perp_y * moveSpeed)][(int)(vars->pov->pos_x - 0.1)] != '1') 
			vars->pov->pos_y += dir_perp_y * moveSpeed;
		else
		{
			printf("hit wall\n");
		}
	}
}

void	hook_move_right(t_vars *vars, double moveSpeed, double dir_perp_x, double dir_perp_y)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		if(vars->cube->map[(int)(vars->pov->pos_y + 0.1)][(int)(vars->pov->pos_x - dir_perp_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - 0.1)][(int)(vars->pov->pos_x - dir_perp_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x - dir_perp_x * moveSpeed + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x - dir_perp_x * moveSpeed - 0.1)] != '1') 
			vars->pov->pos_x -= dir_perp_x * moveSpeed;
		if(vars->cube->map[(int)(vars->pov->pos_y - dir_perp_y * moveSpeed + 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - dir_perp_y * moveSpeed - 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - dir_perp_y * moveSpeed)][(int)(vars->pov->pos_x + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - dir_perp_y * moveSpeed)][(int)(vars->pov->pos_x - 0.1)] != '1') 
			vars->pov->pos_y -= dir_perp_y * moveSpeed;
		else
		{
			printf("hit wall\n");
		}
	}
}
