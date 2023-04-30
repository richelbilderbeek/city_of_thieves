FROM ubuntu:latest

LABEL description = "Image for the game City Of Thieves"
MAINTAINER "Richèl Bilderbeek" richel@richelbilderbeek.nl

# Use bash as shell
SHELL ["/bin/bash", "--login", "-c"]

# Set timezone
ENV TZ="Europe/Stockholm"
ENV DEBIAN_FRONTEND=noninteractive

COPY Makefile ./
COPY Classes ./
COPY ClassesTest ./
COPY Console ./
COPY Files ./

# Install package for setting timezone
RUN apt-get update && apt-get install -y tzdata

COPY install_packages.sh ./

RUN ./install_packages.sh

RUN cat Makefile > temp_makefile.txt
RUN find . > temp_all_files.txt

RUN make console_test

RUN Console/CityOfThievesConsoleTest

RUN make console
