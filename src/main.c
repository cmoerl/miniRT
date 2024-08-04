/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:56:02 by csturm            #+#    #+#             */
/*   Updated: 2024/08/04 14:57:58 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int main(int argc, char **argv)
{
    t_scene scene = {0};

    if (argc != 2)
    {
        printf("Usage: %s <scene.rt>\n", argv[0]);
        return 1;
    }

    // Test check_file function
    check_file(argv[1]);

    // If the file is valid, proceed with parsing (placeholder)
    scene = parse_scene(argv[1], scene);

    // Print parsed ambient lighting for testing
    printf("Ambient lighting intensity: %f\n", scene.amblight.intensity);
    printf("Ambient lighting color: %f, %f, %f\n", scene.amblight.color.r, scene.amblight.color.g, scene.amblight.color.b);

    return 0;
}

 