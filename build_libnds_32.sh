#!/bin/bash

# Create folder structure
sudo mkdir -p /opt/devkitpro
sudo chmod 777 /opt/devkitpro
# Go to that folder
cd /opt/devkitpro
# Download and extract devkitARM
sudo wget https://sourceforge.net/projects/devkitpro/files/devkitARM/devkitARM_r46/devkitARM_r46-i686-linux.tar.bz2
# Extract
sudo tar -xvjf devkitARM_r46-i686-linux.tar.bz2
# libnds
mkdir libnds
cd libnds
sudo wget https://sourceforge.net/projects/devkitpro/files/libnds/1.7.1/libnds-1.7.1.tar.bz2
sudo tar -xvjf libnds-1.7.1.tar.bz2
# libfat (subfolder of libnds)
sudo wget https://sourceforge.net/projects/devkitpro/files/libfat/1.1.2/libfat-nds-1.1.2.tar.bz2
sudo tar -xvjf libfat-nds-1.1.2.tar.bz2
# dswifi (subfolder of libnds)
sudo wget https://sourceforge.net/projects/devkitpro/files/dswifi/0.4.0/dswifi-0.4.0.tar.bz2
sudo tar -xvjf dswifi-0.4.0.tar.bz2
# maxmod (subfolder of libnds)
sudo wget https://sourceforge.net/projects/devkitpro/files/maxmod/1.0.10/maxmod-nds-1.0.10.tar.bz2
sudo tar -xvjf maxmod-nds-1.0.10.tar.bz2
# libfilesystem (subfolder of libnds)
sudo wget https://sourceforge.net/projects/devkitpro/files/filesystem/0.9.13-1/libfilesystem-0.9.13-1.tar.bz2
sudo tar -xvjf libfilesystem-0.9.13-1.tar.bz2
# default_arm7 (subfolder of libnds)
sudo wget https://sourceforge.net/projects/devkitpro/files/default_arm7/0.7.3/default_arm7-0.7.3.tar.bz2
sudo tar -xvjf default_arm7-0.7.3.tar.bz2
# Go to /opt/devkitpro
cd ..
# Examples
mkdir -p examples/nds
cd examples/nds
sudo wget https://sourceforge.net/projects/devkitpro/files/examples/nds/nds-examples-20170915.tar.bz2
sudo tar -xvjf nds-examples-20170915.tar.bz2
