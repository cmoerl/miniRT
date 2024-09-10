/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:18:53 by csturm            #+#    #+#             */
/*   Updated: 2024/09/10 20:52:09 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

//This function  is searching for Ambient light, Camera, Light, and Objects in the scene description
void	parse_scene_line(char *line, t_scene *scene)
{
	int	i;

	i = 0;
	skip_whitespace(line, &i);
	if (line[i] == '\0' || line[i] == '\n')
		return ;
	if (line[i] == 'A')
		parse_ambient_line(&line[i], scene);
	else if (line[i] == 'C')
		parse_camera_line(&line[i], scene);
	else if (line[i] == 'L')
		parse_light_line(&line[i], scene);
	else
	{
		parse_object_line(&line[i], scene);
	}
}

//This function reads and parses the lines of a scene description from a file
void	read_and_parse_lines(t_scene *scene)
{
	char	*line;

	line = get_next_line(scene->fd, 0);
	while (line != NULL)
	{
		parse_scene_line(line, scene);
		free(line);
		line = get_next_line(scene->fd, 0);
	}
}

//This function reads and parses a scene description from a file,
//Initializes the scene, and performs various checks to ensure the scene is valid.
t_scene	parse_scene(char *file, t_scene scene)
{
	scene.flags = (t_flags){0, 0, 0, 0, 0, 0, 0, 0};
	scene = init_scene(scene);
	scene.fd = open(file, O_RDONLY);
	if (scene.fd < 0)
		error("Could not open file", &scene, NULL);
	read_and_parse_lines(&scene);
	check_essential_components(&scene, NULL);
	close(scene.fd);
	scene.fd = -1;
	if (!scene.flags.objects_found)
		error("No objects found in scene", &scene, NULL);
	else if (scene.flags.invalid_line_found)
		error("Invalid line found in scene", &scene, NULL);
	return (scene);
}
