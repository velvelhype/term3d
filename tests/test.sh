#!/bin/sh -x

# NO argument
./term3d

# INVALID argument
./term3d abcde

# TOO MANY
./term3d a b

# file NOT exist
./term3d abcde.ply

# file exist, but NOT ply
./term3d main.c

# ply file, but INVALID format
./term3d invalid.ply

# good ply file, but TOO MANY args
./term3d ./obj/corn.ply a

# good ply files, but TOO MANY
./term3d ./obj/corn.ply ./obj/cube.ply
