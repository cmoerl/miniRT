/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:41:08 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/02 17:41:26 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_intensity(char *line, int *i, float *intensity, t_scene *scene)
{
    int	start;
    scene->flags.dot_count = 0;
    scene->flags.sign_count = 0;

    start = *i;
    if (line[*i] == '-' || line[*i] == '+')
    {
        scene->flags.sign_count++;
        (*i)++;
    }
    while (line[*i] && (ft_isdigit(line[*i]) || line[*i] == '.'))
    {
        if (line[*i] == '.')
            scene->flags.dot_count++;
        (*i)++;
    }
    if (start == *i || scene->flags.dot_count > 1 || scene->flags.sign_count > 1)
        error("Invalid input in ambient lighting definition", scene, line);
    *intensity = ft_atof(&line[start]);
    if (*intensity < 0.0 || *intensity > 1.0)
        error("Ambient lighting intensity out of range [0.0, 1.0]", scene, line);
}

void	parse_color_value(char *line, int *i, t_color_info *color_info, t_scene *scene)
{
    int	start;
    scene->flags.dot_count = 0;
    scene->flags.sign_count = 0;

    start = *i;
    if (line[*i] == '-' || line[*i] == '+')
    {
        scene->flags.sign_count++;
        (*i)++;
    }
    while (line[*i] && (ft_isdigit(line[*i]) || line[*i] == '.'))
    {
        if (line[*i] == '.')
            scene->flags.dot_count++;
        (*i)++;
    }
    if (start == *i || scene->flags.dot_count > 1 || scene->flags.sign_count > 1 || (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != ',' && line[*i] != '\n'))
        error("Invalid input in ambient lighting definition", scene, line);
    *(color_info->color_value) = ft_atoi(&line[start]);
    if (*(color_info->color_value) < 0 || *(color_info->color_value) > 255)
    {
        printf("Error: Ambient lighting %s value out of range [0, 255]\n", color_info->color_name);
        error(NULL, scene, line);
    }
}

void	parse_color_values(char *line, int *i, t_color *color, t_scene *scene)
{
    int				r;
    int				g;
    int				b;
    t_color_info	color_info;

    scene->flags.comma_count = 0;

    color_info.color_value = &r;
    color_info.color_name = "red";
    parse_color_value(line, i, &color_info, scene);
    while (line[*i] && (line[*i] == ' ' || line[*i] == '\t' || line[*i] == ','))
    {
        if (line[*i] == ',')
            scene->flags.comma_count++;
        (*i)++;
    }
    if (scene->flags.comma_count > 1)
    {
        printf("Error: Multiple ',' characters in color values\n");
        error("Invalid input in ambient lighting definition", scene, line);
    }
    color_info.color_value = &g;
    color_info.color_name = "green";
    parse_color_value(line, i, &color_info, scene);
    scene->flags.comma_count = 0;
    while (line[*i] && (line[*i] == ' ' || line[*i] == '\t' || line[*i] == ','))
    {
        if (line[*i] == ',')
            scene->flags.comma_count++;
        (*i)++;
    }
    if (scene->flags.comma_count > 1)
    {
        printf("Error: Multiple ',' characters in color values\n");
        error("Invalid input in ambient lighting definition", scene, line);
    }
    color_info.color_value = &b;
    color_info.color_name = "blue";
    parse_color_value(line, i, &color_info, scene);
    while (line[*i] && (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n'))
        (*i)++;
    color->r = r / 255.0;
    color->g = g / 255.0;
    color->b = b / 255.0;
}

void	parse_ambient(char *line, t_amblight *ambient, t_scene *scene)
{
    int		i;
    float	intensity;

    i = 0;
    skip_whitespace(line, &i);
    if (line[i] != 'A')
        error("Missing 'A' identifier for ambient lighting", scene, line);
    i++;
    skip_whitespace(line, &i);
    parse_intensity(line, &i, &intensity, scene);
    skip_whitespace(line, &i);
    parse_color_values(line, &i, &ambient->color, scene);
    if (line[i] != '\0')
        error("Invalid input in ambient lighting definition", scene, line);
    ambient->intensity = intensity;
}