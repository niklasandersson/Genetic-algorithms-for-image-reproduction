#version 430 core

layout (local_size_x = 32, local_size_y = 32) in;

layout (binding = 0, r32f) readonly uniform image2D orig_image;
layout (binding = 1, r32f) readonly uniform image2D creature_image;

void main() {

}
