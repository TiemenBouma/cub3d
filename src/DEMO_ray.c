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

void verLine(mlx_image_t *img, int x, int drawStart, int drawEnd, int color)
{
	int i;
	
	i = 0;
	while (i + drawStart < drawEnd)
	{


		if (x == SCREEN_X / 2)
			mlx_put_pixel(img, x, drawStart + i, 0xff0000ff);
		else
			mlx_put_pixel(img, x, drawStart + i, color);
		i++;
	}
}

void func(t_vars *vars, t_pov *pov)
{
	(void)pov;

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

	x = 0;
	w = SCREEN_X;

		while (x < w)
		{


			camera_x = 2 * x / (double) w - 1; //range beween -1 and 1;
			//printf("DEBUG: x = %d w = %d camara_x = %f\n", x, w, camera_x);
			raydir_x = pov->dir_x + pov->plane_x * camera_x;
			raydir_y = pov->dir_y + pov->plane_y * camera_x;
			//printf("raydirx = %f, raydir y = %f\n\n", raydir_x, raydir_y);
			//usleep(10000);

			map_x = (int)pov->pos_x;
			map_y = (int)pov->pos_y;
			

			// sidedist_x = 0;
			// sidedist_y = 0;

			if (raydir_x == 0)
				delta_dist_x = 1e30;
			else
				delta_dist_x = ft_abs(1 / raydir_x);
			if (raydir_y == 0)
				delta_dist_y = 1e30;
			else
				delta_dist_y = ft_abs(1 / raydir_y);
			//printf("raydir_x %f delta x %f, raydir_y %f delta y %f\n", raydir_x, delta_dist_x, raydir_y, delta_dist_y);

			// perp_wall_dist = 0;
			// step_x = 0;
			// step_y = 0;
			hit = 0;
			wall_side = 0;


			if ( raydir_x < 0)
			{
				step_x = -1;
				sidedist_x = (pov->pos_x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				sidedist_x = (map_x + 1.0 - pov->pos_x) * delta_dist_x;
			}
			if ( raydir_y < 0)
			{
				step_y = -1;
				sidedist_y = (pov->pos_y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				sidedist_y = (map_y + 1.0 - pov->pos_y) * delta_dist_y;
			}
			// printf("sidedistx: %f, sidedisty: %f\n", sidedist_x, sidedist_y);
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
				// print_map(vars->cube->map);
				// printf("mapx %d, mapy = %d\n", map_x, map_y);
				if (vars->cube->map[map_y][map_x] == '1')
				{
					//printf("DEBUG: while map = %c\n\n", vars->cube->map[map_x][map_y]);
					hit = 1;
				}
			}
			// printf("map[17[18]: %c\n", vars->cube->map[map_y][map_x]);
			//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
			//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
			//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
			//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
			//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
			//steps, but we subtract deltaDist once because one step more into the wall was taken above.

			if(wall_side == 0)
				perp_wall_dist = (sidedist_x - delta_dist_x);//sidedist_x;//
			else
				perp_wall_dist =(sidedist_y - delta_dist_y); //sidedist_y;//

			double wallx = 0; //where exactly the wall was hit
			if (wall_side == 0)
				wallx = pov->pos_y + perp_wall_dist * raydir_y;
			else
				wallx = pov->pos_x + perp_wall_dist * raydir_x;

			int	wall_ori = 0;
			if (wall_side == 0 && delta_dist_x >= 0)
				wall_ori = 'E';
			else if (wall_side == 0 && delta_dist_x < 0)
				wall_ori = 'W';
			else if (wall_side == 1 && delta_dist_y >= 0)
				wall_ori = 'S';
			else if (wall_side == 1 && delta_dist_y < 0)
				wall_ori = 'N';

			double scale;
			scale = 1 / perp_wall_dist;

			// printf("DEBUG: scale: %f\n", scale);
			// printf("DEBUG: prep_wall_dist = %f\n", perp_wall_dist);
			print_line(vars->cube, wallx, wall_ori, scale, x);
      		//Calculate height of line to draw on screen			
			int lineHeight = (int)(SCREEN_Y / perp_wall_dist);//????????

      		//calculate lowest and highest pixel to fill in current stripe
			//printf("lineh %d, -lineh %d\n\n", lineHeight, -lineHeight);
	  		drawStart = SCREEN_Y / 2 - lineHeight / 2;
			if(drawStart < 0)
				drawStart = 0;
			drawEnd = lineHeight / 2 + SCREEN_Y / 2;
			if(drawEnd >= SCREEN_Y)
				drawEnd = SCREEN_Y - 1;

			//CHOOSE WALL TEXTURE or COLOR
			//color = 0xff0000ff;
			switch(vars->cube->map[map_y][map_x])
			{
				case 1:  color = 0xff0000ff;    break; //red
				case 2:  color = 0x00ff00ff;  break; //green
				case 3:  color = 0x0000ffff;   break; //blue
				case 4:  color = 0xffffffff;  break; //white
				default: color = 0x888800ff; break; //yellow
			}

			//give x and y sides different brightness
			if(wall_side == 1)
				color = 0x880000ff;
			//mlx_delete_image(vars->mlx, vars->cube->g_img_DEMO);
			//vars->cube->g_img_DEMO = mlx_new_image(vars->mlx, 1000, 1000);

			// verLine(vars->cube->g_img_DEMO, x, drawStart, drawEnd, color);

			//printf("DEBUG: while x = %d, w = %d\n\n", x, w);
			x++;
		}
		//return (img);

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