#!/bin/bash
#
# Unindents text in all markdown files
#
# For an indented block, a link to a broken image is ignored, as the link checker assumes it to be code.
# In our case, it is not: for us, it is usually an admonition (i.e. a 'question' or 'info' block)
# Here all indented text is unindented
# https://github.com/UPPMAX/UPPMAX-documentation/issues/114
#
for filename in $(find . | grep .md)
do
sed -i 's/^    //g' "${filename}"
sed -i 's/^    //g' "${filename}"
sed -i 's/^    //g' "${filename}"
done
