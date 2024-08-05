/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:18:53 by csturm            #+#    #+#             */
/*   Updated: 2024/08/05 08:45:49 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* 
- parse the file into structs defined in minirt.h
- return a t_scene struct that holds all other structs
*/

void check_file(char *file)
{
    // Check if file is accessible
    if (!file || access(file, F_OK) == -1)
    {
        perror("Error accessing file");
        exit(EXIT_FAILURE);
    }

    // Check if file has .rt extension
    char *extension = ft_strrchr(file, '.');
    if (!extension || ft_strcmp(extension, ".rt") != 0)
    {
        printf("Error: Incorrect file format. Expected .rt\n");
        exit(EXIT_FAILURE);
    }
}

t_scene init_scene(t_scene scene)
{
    scene.objects = malloc(sizeof(t_object));
    if (!scene.objects)
        error("Memory allocation failed", &scene);
    scene.objects->spheres = NULL;
    scene.objects->planes = NULL;
    scene.objects->cylinders = NULL;
    return scene;
}
t_scene parse_scene(char *file, t_scene scene)
{
    int fd;
    char *line = NULL;
    int ambient_found = 0;
    int camera_found = 0;
    int light_found = 0;

    scene = init_scene(scene);
    check_file(file);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        error("Could not open file", &scene);

    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] == 'A')
        {
            parse_ambient(line, &scene.amblight);
            ambient_found = 1;
        }
        else if (line[0] == 'C')
        {
            parse_camera(line, &scene.camera);
            camera_found = 1;
        }
        else if (line[0] == 'L')
        {
            parse_light(line, &scene.light);
            light_found = 1;
        }
        free(line);
    }

    close(fd);

    // Check for essential components
    if (!ambient_found)
    {
        error("Missing ambient lighting definition", &scene);
    }
    if (!camera_found)
    {
        error("Missing camera definition", &scene);
    }
    if (!light_found)
    {
        error("Missing light definition", &scene);
    }

    return scene;
}