#!/bin/bash
#
# Fix Markdown style errors,
# as is recommended by the Markdown checker.
#
# Usage:
#
#   ./scripts/fix_markdown_style_errors.sh

if [[ "$PWD" =~ scripts$ ]]; then
    echo "FATAL ERROR."
    echo "Please run the script from the project root. "
    echo "Present working director: $PWD"
    echo " "
    echo "Tip: like this"
    echo " "
    echo "  ./scripts/fix_markdown_style_errors.sh"
    echo " "
    exit 42
fi

markdownlint --fix "**/*.md"
git status

