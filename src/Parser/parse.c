/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:18:53 by csturm            #+#    #+#             */
/*   Updated: 2024/08/04 23:09:40 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* 
- parse the file into structs defined in minirt.h
- return a t_scene struct that holds all other structs
*/

void error(char *message, t_scene *scene)
{
    if (message != NULL)
    {
        write(1, "Error: ", 7);
        write(1, message, ft_strlen(message));
        write(1, "\n", 1);
    }
    if (scene == NULL)
        exit(1);
    if (message != NULL)
        exit(1);
    exit(0);
}

float ft_atof(const char *str)
{
    float result = 0.0;
    float sign = 1.0;
    float factor = 0.1;
    int i = 0;
    // Handle sign
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1.0;
        i++;
    }
    // Parse integer part
    while (ft_isdigit(str[i]))
    {
        result = result * 10.0 + (str[i] - '0');
        i++;
    }
    // Parse fractional part
    if (str[i] == '.')
    {
        i++;
        while (ft_isdigit(str[i]))
        {
            result += (str[i] - '0') * factor;
            factor *= 0.1;
            i++;
        }
    }
    return result * sign;
}

void parse_light(char *line, t_light *light)
{
    int i = 1; // Start after 'L'
    int r, g, b;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse position
    light->position.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    light->position.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    light->position.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse intensity
    light->intensity = ft_atof(&line[i]);
    if (light->intensity < 0.0 || light->intensity > 1.0)
    {
        error("Light intensity out of range [0.0, 1.0]", NULL);
    }

    // Skip to RGB values if present
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse RGB values (if present)
    if (line[i])
    {
        r = ft_atoi(&line[i]);
        while (line[i] && line[i] != ',')
            i++;
        if (line[i] == ',') i++;

        g = ft_atoi(&line[i]);
        while (line[i] && line[i] != ',')
            i++;
        if (line[i] == ',') i++;

        b = ft_atoi(&line[i]);

        // Validate RGB values
        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        {
            error("Light color values out of range [0, 255]", NULL);
        }
    }
    else
    {
        r = 255;
        g = 255;
        b = 255;
    }

    printf("Parsed light position: %f, %f, %f\n", light->position.x, light->position.y, light->position.z);
    printf("Parsed light intensity: %f\n", light->intensity);
    printf("Parsed light color: %d, %d, %d\n", r, g, b);
}

void parse_camera(char *line, t_camera *camera)
{
    int i = 1; // Start after 'C'

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse position (center)
    camera->center.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    camera->center.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    camera->center.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse orientation
    camera->orientation.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    camera->orientation.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    camera->orientation.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse FOV
    camera->fov = ft_atof(&line[i]);
    if (camera->fov < 0 || camera->fov > 180)
    {
        error("Camera FOV out of range [0, 180]", NULL);
    }
}

void parse_ambient(char *line, t_amblight *ambient)
{
    int i = 1; // Start after 'A'
    float intensity;
    int r, g, b;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    // Check for invalid characters in intensity
    if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
    {
        error("Invalid character in ambient lighting intensity", NULL);
    }
    // Parse intensity
    intensity = ft_atof(&line[i]);
    if (intensity < 0.0 || intensity > 1.0)
    {
        error("Ambient lighting intensity out of range [0.0, 1.0]", NULL);
    }
    printf("Parsed intensity: %f\n", intensity);

    // Move index to next part (skipping the intensity part)
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Check for invalid characters in red value
    if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
    {
        error("Invalid character in ambient lighting red value", NULL);
    }
    // Parse RGB values
    r = ft_atoi(&line[i]);
    if (r < 0 || r > 255)
    {
        error("Ambient lighting red value out of range [0, 255]", NULL);
    }
    printf("Parsed red: %d\n", r);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',')
        i++;
    // Check for invalid characters in green value
    if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
    {
        error("Invalid character in ambient lighting green value", NULL);
    }
    g = ft_atoi(&line[i]);
    if (g < 0 || g > 255)
    {
        error("Ambient lighting green value out of range [0, 255]", NULL);
    }
    printf("Parsed green: %d\n", g);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',')
        i++;

    // Check for invalid characters in blue value
    if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
    {
        error("Invalid character in ambient lighting blue value", NULL);
    }

    b = ft_atoi(&line[i]);
    if (b < 0 || b > 255)
    {
        error("Ambient lighting blue value out of range [0, 255]", NULL);
    }
    printf("Parsed blue: %d\n", b);

    // Check for unexpected characters after parsing
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i] && !ft_isdigit(line[i]) && line[i] != '\0')
    {
        error("Unexpected character in ambient lighting definition", NULL);
    }

    // Set the values in the ambient struct
    ambient->intensity = intensity;
    ambient->color.r = r / 255.0;
    ambient->color.g = g / 255.0;
    ambient->color.b = b / 255.0;
}

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