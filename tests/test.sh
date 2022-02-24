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
./term3d ./ply_files/corn.ply a

# good ply files, but TOO MANY
./term3d ./ply_files/corn.ply ./ply_files/cube.ply
./term3d ply_files/invalid_files/00_dup_face.ply
./term3d ply_files/invalid_files/01_dup_vtx.ply
./term3d ply_files/invalid_files/02_invalid_face.ply
./term3d ply_files/invalid_files/03_invalid_vertex.ply
./term3d ply_files/invalid_files/04_few_vtx_in_face.ply
./term3d ply_files/invalid_files/05_large_coordinates.ply
./term3d ply_files/invalid_files/06_many_vtx_in_face.ply
./term3d ply_files/invalid_files/07_no_face.ply
./term3d ply_files/invalid_files/08_no_ply.ply
./term3d ply_files/invalid_files/09_no_vertex.ply
./term3d ply_files/invalid_files/10_same_vtx_in_face.ply
