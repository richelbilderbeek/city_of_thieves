#!/bin/bash
#
# Build a Docker image
#
# Usage:
#
#   ./scripts/build_docker_image.sh
#
#
sudo docker build -f Dockerfile -t city_of_thieves .
