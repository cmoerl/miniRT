# miniRT

## Overview

miniRT is a project that implements a simple ray tracer. The project involves rendering 3D scenes by simulating the way rays of light interact with objects in the scene.

## Features

- Renders 3D scenes using ray tracing.
- Supports multiple object types including spheres, planes, and cylinders.
- Calculates lighting and shadows.
- Configurable camera settings.

## Installation

### Prerequisites

- Unix-like operating system (Linux, macOS).
- GCC compiler.
- Make utility.

### Compilation

To compile the project, clone the repository and run make:

    git clone https://github.com/cmoerl/minirt.git
    cd minirt
    make

This will generate an executable named miniRT.

### Usage

To run the program, use the following command:

    ./miniRT scene_file.rt

#### Parameters

    scene_file.rt: Path to the scene description file.

#### Example

    ./miniRT scenes/example.rt

This command starts rendering the scene described in example.rt.

### Scene File Format

The scene file is a plain text file that describes the objects, lights, and camera settings in the scene. Here is an example:

    C 0,0,20 0,0,-1 70

    L 10,10,10 1.0 255,255,255

    sp 0,0,0 5 255,0,0
    pl 0,-5,0 0,1,0 0,255,0
    cy 5,0,0 0,1,0 2 10 0,0,255

