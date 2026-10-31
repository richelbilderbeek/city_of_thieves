#!/bin/bash
#
# Install markdownlint
#
# Do not do ...
#
#   sudo apt install markdownlint # DONT!
#
# as this is a different tool as used by the GitHub Action.
#
# Do not do ...
#
#   npm install markdownlint # DONT!
#
# as this is a different tool as used by the GitHub Action.
#
sudo npm install -g markdownlint-cli
