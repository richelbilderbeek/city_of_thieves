#!/bin/bash
find . -name '*.gcno' | while read -r gcno
do
  objdir=$(dirname "${gcno}")
  base=$(basename "${gcno}" .gcno)
  cpp=$(find . -name "${base}.cpp" | head -n 1)
  if [ -z "${cpp}" ]; then
    echo "No source for ${gcno}" >&2
    continue
  fi
  gcov -n -o "${objdir}" "${cpp}" > /dev/null
done
