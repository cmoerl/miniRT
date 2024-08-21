/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:18:53 by csturm            #+#    #+#             */
/*   Updated: 2024/08/21 19:07:36 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"


void	parse_scene_line(char *line, t_scene *scene,
		int *ambient_found, int *camera_found, int *light_found)
{
	int	i;

	i = 0;
	skip_whitespace(line, &i);
	if (line[i] == '\0' || line[i] == '\n')
		return ;
	if (line[i] == 'A')
	{
		parse_ambient_line(&line[i], scene, ambient_found);
	}
	else if (line[i] == 'C')
	{
		parse_camera_line(&line[i], scene, camera_found);
	}
	else if (line[i] == 'L')
	{
		parse_light_line(&line[i], scene, light_found);
	}
	else
	{
		parse_object_line(&line[i], scene);
	}
}


void	read_and_parse_lines(int fd, t_scene *scene, int *ambient_found,
		int *camera_found, int *light_found)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		parse_scene_line(line, scene, ambient_found, camera_found, light_found);
		free(line);
		line = get_next_line(fd);
	}
}

t_scene	parse_scene(char *file, t_scene scene)
{
	int	fd;
	int	ambient_found;
	int	camera_found;
	int	light_found;

	ambient_found = 0;
	camera_found = 0;
	light_found = 0;
	scene = init_and_check_file(file, scene);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Could not open file", &scene);
	read_and_parse_lines(fd, &scene, &ambient_found,
		&camera_found, &light_found);
	close(fd);
	check_essential_components(ambient_found, camera_found,
		light_found, &scene);
	return (scene);
}
