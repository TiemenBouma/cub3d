#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24

double ft_abs (double i)
{
  return i < 0 ? -i : i;
}

char	determain_wall()
{
	return (0);
}

void calc_raydir(t_ray *ray, t_pov *pov, double camera_x)
{
	ray->dir_x = pov->dir_x + pov->plane_x * camera_x;
	ray->dir_y = pov->dir_y + pov->plane_y * camera_x;
}

void calc_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = ft_abs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = ft_abs(1 / ray->dir_y);
}

void calc_side_dist(t_ray *ray, char **map)
{
	int	hit;
	
	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->wall_side = 0;
		}
		else
		{
			ray->sidedist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->wall_side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void calc_initial_side_dist(t_ray *ray, t_pov *pov)
{
	if ( ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (pov->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - pov->pos_x) * ray->delta_dist_x;
	}
	if ( ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (pov->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - pov->pos_y) * ray->delta_dist_y;
	}
}

void	calc_perp_wall_dist(t_ray *ray)
{
	if(ray->wall_side == 0)
		ray->perp_wall_dist = (ray->sidedist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist =(ray->sidedist_y - ray->delta_dist_y);

}

void	calc_wall_ori(t_ray *ray)
{
	if (ray->dir_x >= 0 && ray->dir_y >= 0)		//quadrant 1
	{
		if (ray->wall_side == 0)
			ray->wall_ori = 'N';
		else
			ray->wall_ori = 'E';
	}
	else if (ray->dir_x >= 0 && ray->dir_y < 0)	//quadrant 2
	{
		if (ray->wall_side == 0)
			ray->wall_ori = 'N';
		else
			ray->wall_ori = 'W';
	}
	else if (ray->dir_x < 0 && ray->dir_y < 0)	//quadrant 3
	{
		if (ray->wall_side == 0)
			ray->wall_ori = 'S';
		else
			ray->wall_ori = 'W';
	}
	else 									//quadrant 4
	{
		if (ray->wall_side == 0)
			ray->wall_ori = 'S';
		else
			ray->wall_ori = 'E';
	}
}

int raycaster()
{

	return (0);
}

void func(t_vars *vars, t_pov *pov)
{
	t_ray	ray;
	//(void)pov;

	int		x;
	int		w;

	double camera_x;
	//double ray.dir_x;
	//double ray.dir_y;
	// int		map_x;
	// int		map_y;
	// double sidedist_x;
	// double sidedist_y;
	// double	delta_dist_x;
	// double	delta_dist_y;

	// double	perp_wall_dist;
	// int step_x;
	// int step_y;
	// int hit;
	// int wall_side;

	// int drawStart;
	// int drawEnd;

	// int color;

	x = 0;
	w = SCREEN_X;

		while (x < w)
		{
			camera_x = 2 * x / (double) w - 1; //range beween -1 and 1;
			calc_raydir(&ray, pov, camera_x);
			//printf("DEBUG: x = %d w = %d camara_x = %f\n", x, w, camera_x);
			//printf("raydirx = %f, raydir y = %f\n\n", ray.dir_x, ray.dir_y);
			//usleep(10000);
			ray.map_x = (int)pov->pos_x;
			ray.map_y = (int)pov->pos_y;
			calc_delta_dist(&ray);

			//printf("ray.dir_x %f delta x %f, ray.dir_y %f delta y %f\n", ray.dir_x, delta_dist_x, ray.dir_y, delta_dist_y);
			calc_initial_side_dist(&ray, pov);
			calc_side_dist(&ray, vars->cube->map);
			calc_perp_wall_dist(&ray);

			// printf("sidedistx: %f, sidedisty: %f\n", sidedist_x, sidedist_y);
			calc_wall_ori(&ray);


			double wallx = 0; //where exactly the wall was hit
			if (ray.wall_side == 0)
				wallx = pov->pos_y + ray.perp_wall_dist * ray.dir_y;
			else
				wallx = pov->pos_x + ray.perp_wall_dist * ray.dir_x;

			// which wall is hit
			// int	wall_ori = 0;
			// calc_wall_ori(&ray);

			double scale;
			scale = 1 / ray.perp_wall_dist;

			// printf("DEBUG: scale: %f\n", scale);
			// printf("DEBUG: prep_wall_dist = %f\n", perp_wall_dist);
			print_line(vars->cube, wallx, ray.wall_ori, scale, x);
      		//Calculate height of line to draw on screen			
			// int lineHeight = (int)(SCREEN_Y / ray.perp_wall_dist);

      		// //calculate lowest and highest pixel to fill in current stripe
			// //printf("lineh %d, -lineh %d\n\n", lineHeight, -lineHeight);
	  		// drawStart = SCREEN_Y / 2 - lineHeight / 2;
			// if(drawStart < 0)
			// 	drawStart = 0;
			// drawEnd = lineHeight / 2 + SCREEN_Y / 2;
			// if(drawEnd >= SCREEN_Y)
			// 	drawEnd = SCREEN_Y - 1;

			// //CHOOSE WALL TEXTURE or COLOR
			// //color = 0xff0000ff;
			// switch(vars->cube->map[map_y][map_x])
			// {
			// 	case 1:  color = 0xff0000ff;    break; //red
			// 	case 2:  color = 0x00ff00ff;  break; //green
			// 	case 3:  color = 0x0000ffff;   break; //blue
			// 	case 4:  color = 0xffffffff;  break; //white
			// 	default: color = 0x888800ff; break; //yellow
			// }

			// //give x and y sides different brightness
			// if(wall_side == 1)
			// 	color = 0x880000ff;
			//mlx_delete_image(vars->mlx, vars->cube->g_img_DEMO);
			//vars->cube->g_img_DEMO = mlx_new_image(vars->mlx, 1000, 1000);

			// verLine(vars->cube->g_img_DEMO, x, drawStart, drawEnd, color);

			//printf("DEBUG: while x = %d, w = %d\n\n", x, w);
			x++;
		}
		//return (img);

}