# Author: Claudio Correa, 2021/05/15

# Ref.: https://cmake.org/examples
# To build, use these commands:
#
# mkdir build		# Create a build directory
# cd build && cmake ..	# Build from that directory so the build files are in one place
# cmake --build .	# Build the project

cmake_minimum_required(VERSION 3.14...3.18)

project(myproject
  VERSION
    1.0
  DESCRIPTION
    "Projeto confecionado para controle de lista de eventos "
  LANGUAGES
    C 
)
