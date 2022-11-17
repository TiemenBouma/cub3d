/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 10:40:42 by tiemen        #+#    #+#                 */
/*   Updated: 2022/11/17 10:52:59 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
//#include "../includes/libft/libft.h"
#include <stdlib.h>

//#include <stdio.h>

void	delete_textures(t_cube *cube)
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

void	free_all(t_vars *vars)
{
	free_double_ptr(vars->cube->map);
	free_double_ptr(vars->cube->cpy_map);
	delete_textures(vars->cube);
	free(vars->cube->no);
	free(vars->cube->ea);
	free(vars->cube->so);
	free(vars->cube->we);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_cube	cube;
	t_file	file;
	mlx_t	*mlx;
	t_pov	pov;

	if (argc != 2)
		error_msg_exit("Error: No file or more than 1 file specified.\n", 1);
	vars.cube = &cube;
	vars.file = &file;
	vars.pov = &pov;
	init_structs(&vars, argv);
	parsing(&vars);
	pov.pos_x = cube.player_x + 0.5;
	pov.pos_y = cube.player_y + 0.5;
	mlx = init_mlx_stuff(&cube);
	vars.mlx = mlx;
	game_loop_mlx(&vars);
	free_all(&vars);
	return (0);
}
