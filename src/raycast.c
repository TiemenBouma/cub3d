#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void raycaster(t_vars *vars, t_pov *pov)
{
	t_ray	ray;
	int		x;
	//int		w;
	double camera_x;

	x = 0;
	//w = SCREEN_X;

	while (x < SCREEN_X)
	{
		camera_x = 2 * x / (double) SCREEN_X - 1; //range beween -1 and 1;
		camera_x *= -1;
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
		calc_wall_x(&ray, pov);
		ray.scale = 1 / ray.perp_wall_dist;

		//printf("DEBUG: \n");
		// printf("DEBUG: prep_wall_dist = %f\n", perp_wall_dist);
		print_line(vars->cube, x, &ray);
		x++;
	}
}