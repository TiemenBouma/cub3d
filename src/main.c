#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>

#include <stdio.h>

void delete_textures(t_cube *cube)
{
	
		if (cube->texture_no_wall != NULL)
			mlx_delete_texture(cube->texture_no_wall);
		if (cube->texture_ea_wall != NULL)
			mlx_delete_texture(cube->texture_ea_wall);
		if (cube->texture_so_wall != NULL)
			mlx_delete_texture(cube->texture_so_wall);
		if (cube->texture_we_wall != NULL)
			mlx_delete_texture(cube->texture_we_wall);
}

void delete_image(mlx_t *mlx, t_cube *cube)
{
	if (cube->g_img_ceilling != NULL)
	{
		printf("DEBUG: DELETE IMG C\n");
		mlx_delete_image(mlx, cube->g_img_ceilling);
	}
	if (cube->g_img_floor != NULL)
	{
		printf("DEBUG: DELETE IMG F\n");

		mlx_delete_image(mlx, cube->g_img_floor);
	}
	if (cube->g_img_DEMO != NULL)
	{
		printf("DEBUG: DELETE IMG DEMO\n");

		mlx_delete_image(mlx, cube->g_img_DEMO);
	}

}

void free_all(t_vars *vars)
{
	free_double_ptr(vars->cube->map);
	printf("DEBUG free\n");
	free_double_ptr(vars->cube->cpy_map);
	printf("DEBUG free1\n");
	//delete_image(vars->mlx, vars->cube);
	printf("DEBUG free2\n");
	//delete_textures(vars->cube);
	printf("DEBUG free3\n");
	free(vars->cube->no);
	free(vars->cube->ea);
	free(vars->cube->so);
	free(vars->cube->we);
}

int main(int argc, char **argv)
{
	t_vars	vars;
	t_cube	cube;
	t_file	file;
	mlx_t	*mlx;
	t_pov	pov;

	if (argc != 2)
	{
		ft_putstr_fd("Error: No file or more than 1 file specified.\n", 2);
		exit (1);
	}
	vars.cube = &cube;
	vars.file = &file;
	vars.pov = &pov;
	init_structs(&vars, argv);
	parsing(&vars);
	pov.pos_x = cube.player_x + 0.5;
	pov.pos_y = cube.player_y + 0.5;
	mlx = init_mlx_stuff(&cube);

	//find_playpos(&cube, &pov);
	//cube.g_img_DEMO = mlx_new_image(mlx, SCREEN_X, SCREEN_Y);
	//cast_rays(&cube, cube.map, &pov);
	//mlx_image_to_window(mlx, cube.g_img_DEMO, 0, 0);
	vars.mlx = mlx;

	game_loop_mlx(&vars);
	printf("DEBUG main\n");
	free_all(&vars);
	printf("DEBUG main2\n");
	return (0);
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
