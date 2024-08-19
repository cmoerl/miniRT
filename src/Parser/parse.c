/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:18:53 by csturm            #+#    #+#             */
/*   Updated: 2024/08/19 11:43:16 by mafurnic         ###   ########.fr       */
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
        // Skip leading whitespace
        int i = 0;
        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
            i++;

        // Skip empty lines
        if (line[i] == '\0' || line[i] == '\n')
        {
            free(line);
            continue;
        }

        // Check the first character after skipping spaces
        if (line[i] == 'A')
        {
            if (ambient_found)
                error("Multiple ambient lighting definitions found", &scene);
            parse_ambient(&line[i], &scene.amblight);
            ambient_found = 1;
        }
        else if (line[i] == 'C')
        {
            if (camera_found)
                error("Multiple camera definitions found", &scene);
            parse_camera(&line[i], &scene.camera);
            camera_found = 1;
        }
        else if (line[i] == 'L')
        {
            if (light_found)
                error("Multiple light definitions found", &scene);
            parse_light(&line[i], &scene.light);
            light_found = 1;
        }
        else if (line[i] == 'p' && line[i+1] == 'l' && (line[i+2] == ' ' || line[i+2] == '\t'))
        {
            parse_plane(&line[i], &scene.objects->planes);
        }
        else if (line[i] == 'c' && line[i+1] == 'y' && (line[i+2] == ' ' || line[i+2] == '\t'))
        {
            parse_cylinder(&line[i], &scene.objects->cylinders);
        }
        else if (line[i] == 's' && line[i+1] == 'p' && (line[i+2] == ' ' || line[i+2] == '\t'))
        {
            parse_sphere(&line[i], &scene.objects->spheres);
        }
        else
        {
            error("Invalid scene description", &scene);
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
