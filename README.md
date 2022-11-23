# cub3d
Made by:            t-bouma and svos
Program languages:  C

Cub3d is a team schoolproject for Codam Coding College.
The idea was to make a raycasting game engine inspired by Wolfenstein 3d.

How it works:
After downloading use the command "make" to compile the code into a executable.
execute cub3D with a map file like "./cub3D map.cub". The map file should have a .cub extention.

Once started you can move with WASD and mouse or arrow keys.

Mapfile requierments:
The file should hav 7 elements:
NO, EA, SO, WE, F, C, and a map
the winddirections should have a texture.png file. recommended pixels is 1024x1024.
F = Floor. It has a rgb color code.
C = Ceilling It has a rgb color code.
map is a represennation of the world the player can move in. It has '1' for walls, '0' for walkable squares. and "N,S,W,E" for startposition and initial view angle.

Example map file:

NO ./path_to_the_north_texture.png
SO ./path_to_the_south_texture.png
WE ./path_to_the_west_texture.png
EA ./path_to_the_east_texture.png
F 220,100,0
C 225,30,0

111111
100001
100001
1N0001
111111


