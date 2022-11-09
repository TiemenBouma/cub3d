#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24

int ft_abs (int i)
{
  return i < 0 ? -i : i;
}

void verLine(mlx_image_t *img, int x, int drawStart, int drawEnd, int color)
{
	int i;
	
	i = 0;
	while (i + drawStart < drawEnd)
	{
		mlx_put_pixel(img, x, drawStart + i, color);
		i++;
	}
}

void func(t_vars *vars, t_pov *pov)
{
	//char 	**map;
	(void)pov;
	int map[mapWidth][mapHeight]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	double	pos_x = 3;
	double	pos_y = 3;
	double	dir_x = -1;
	double	dir_y = 0;
	double	plane_x = 0;
	double	plane_y = 0.66;
	int		x;
	int		w;

	double camera_x;
	double raydir_x;
	double raydir_y;
	int		map_x;
	int		map_y;
	double sidedist_x;
	double sidedist_y;
	double	delta_dist_x;
	double	delta_dist_y;

	double	perp_wall_dist;
	int step_x;
	int step_y;
	int hit;
	int wall_side;

	int drawStart;
	int drawEnd;

	int color;
	//mlx_t mlx;
	//mlx_image_t *img; 

	x = 0;
	w = SCREEN_X;
	while (1)
	{
		while (x < w)
		{
			camera_x = 2 * x / (double) w - 1;
			raydir_x = dir_x + plane_x * camera_x;
			raydir_y = dir_y + plane_y * camera_x;

			map_x = (int)pos_x;
			map_y = (int)pos_y;

			sidedist_x = 0;
			sidedist_y = 0;

			if (raydir_x == 0)
				delta_dist_x = 1e30;
			else
				delta_dist_x = ft_abs(1 / raydir_x);
			if (raydir_y == 0)
				delta_dist_y = 1e30;
			else
				delta_dist_y = ft_abs(1 / raydir_y);

			perp_wall_dist = 0;
			step_x = 0;
			step_y = 0;
			hit = 0;
			wall_side = 0;

			if ( raydir_x < 0)
			{
				step_x = -1;
				sidedist_x = (pos_x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				sidedist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
			}
			if ( raydir_y < 0)
			{
				step_y = -1;
				sidedist_y = (pos_y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				sidedist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
			}
			while (hit == 0)
			{
				if (sidedist_x < sidedist_y)
				{
					sidedist_x +=delta_dist_x;
					map_x += step_x;
					wall_side = 0;
				}
				else
				{
					sidedist_y += delta_dist_y;
					map_y += step_y;
					wall_side = 1;
				}
				if (map[map_x][map_y] > 0)
				{

					// printf("DEBUG: while map = %d\n\n", map[map_x][map_y]);
					hit = 1;
				}
			}
			//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
			//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
			//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
			//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
			//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
			//steps, but we subtract deltaDist once because one step more into the wall was taken above.

			if(wall_side == 0)
				perp_wall_dist = (sidedist_x - delta_dist_x);
			else
				perp_wall_dist = (sidedist_y - delta_dist_y);
			
      		//Calculate height of line to draw on screen			
			int lineHeight = (int)(SCREEN_Y / perp_wall_dist);//????????

      		//calculate lowest and highest pixel to fill in current stripe
	  		drawStart = -lineHeight / 2 + SCREEN_Y / 2;
			if(drawStart < 0)
				drawStart = 0;
			drawEnd = lineHeight / 2 + SCREEN_Y / 2;
			if(drawEnd >= SCREEN_Y)
				drawEnd = SCREEN_Y - 1;

			//CHOOSE WALL TEXTURE or COLOR
			//color = 0xff0000ff;
			switch(map[map_x][map_y])
			{
				case 1:  color = 0xff0000ff;    break; //red
				case 2:  color = 0x00ff00ff;  break; //green
				case 3:  color = 0x0000ffff;   break; //blue
				case 4:  color = 0xffffffff;  break; //white
				default: color = 0xffff00ff; break; //yellow
			}

			//give x and y sides different brightness
			if(wall_side == 1)
				color = color / 2;
			mlx_delete_image(vars->mlx, vars->cube->g_img_DEMO);
			vars->cube->g_img_DEMO = mlx_new_image(vars->mlx, 1000, 1000);
			verLine(vars->cube->g_img_DEMO, x, drawStart, drawEnd, color);

			printf("DEBUG: while x = %d, w = %d\n\n", x, w);
			x++;
		}
		//return (img);
	}

}

// int main(int argc, char **argv)
// {
// 	t_vars	vars;
// 	t_cube	cube;
// 	t_file	file;
// 	mlx_t	*mlx;
// 	t_pov	pov;

// 	if (argc != 2)
// 	{
// 		ft_putstr_fd("Error: No file or more than 1 file specified.\n", 2);
// 		exit (1);
// 	}
// 	vars.cube = &cube;
// 	vars.file = &file;
// 	init_structs(&vars, argv);
// 	parsing(&cube, &file);
// 	mlx = init_mlx_stuff(&cube);
// 	find_playpos(&cube, &pov);
// 	vars.pov = &pov;
// 	//cube.g_img_DEMO = mlx_new_image(mlx, SCREEN_X, SCREEN_Y);
// 	//cast_rays(&cube, cube.map, &pov);
// 	//mlx_image_to_window(mlx, cube.g_img_DEMO, 0, 0);
// 	vars.mlx = mlx;
// 	game_loop_mlx(&vars);
// 	free_all(&vars);
// 	return (0);
// }