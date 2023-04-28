FROM ubuntu:latest

LABEL description = "Image for the game City Of Thieves"
MAINTAINER "Richèl Bilderbeek" richel@richelbilderbeek.nl

# Use bash as shell
SHELL ["/bin/bash", "--login", "-c"]

# Set timezone
ENV TZ="Europe/Stockholm"
ENV DEBIAN_FRONTEND=noninteractive

# Install package for setting timezone
RUN apt-get update && apt-get install -y tzdata libboost-all-dev
