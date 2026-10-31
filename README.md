# Intro to Python for HPC

<!-- markdownlint-disable MD013 --><!-- Badges cannot be split up over lines, hence will break 80 characters per line -->

[![Check links](https://github.com/UPPMAX/naiss_intro_python/actions/workflows/check_links.yaml/badge.svg?branch=main)](https://github.com/UPPMAX/naiss_intro_python/actions/workflows/check_links.yaml)
[![Check Markdown](https://github.com/UPPMAX/naiss_intro_python/actions/workflows/check_markdown.yaml/badge.svg?branch=main)](https://github.com/UPPMAX/naiss_intro_python/actions/workflows/check_markdown.yaml)
[![Check spelling](https://github.com/UPPMAX/naiss_intro_python/actions/workflows/check_spelling.yaml/badge.svg?branch=main)](https://github.com/UPPMAX/naiss_intro_python/actions/workflows/check_spelling.yaml)
[![Create the MkDocs website](https://github.com/UPPMAX/naiss_intro_python/actions/workflows/create_mkdocs_website.yaml/badge.svg?branch=main)](https://github.com/UPPMAX/naiss_intro_python/actions/workflows/create_mkdocs_website.yaml)
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.17700484.svg)](https://doi.org/10.5281/zenodo.17700484)

<!-- markdownlint-enable MD013 -->

- [Go to the nicely rendered site](https://uppmax.github.io/naiss_intro_python/)

## Files used by continuous integration scripts

<!-- markdownlint-disable MD013 --><!-- Tables cannot be split up over lines, hence will break 80 characters per line -->

Filename                                    |Description
--------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------
[`mlc_config.json`](mlc_config.json)        |Configuration of the link checker, use `markdown-link-check --config mlc_config.json --quiet docs/**/*.md` to do link checking locally
[`.spellcheck.yml`](.spellcheck.yml)        |Configuration of the spell checker, use [`./scripts/check_spelling.sh`](scripts/check_spelling.sh) to do spell check locally
[`.wordlist.txt`](.wordlist.txt)            |Whitelisted words for the spell checker, use [`./scripts/check_spelling.sh`](scripts/check_spelling.sh) to do spell check locally
[`.markdownlint.jsonc`](.markdownlint.jsonc)|Configuration of the Markdown linter, use [`./scripts/fix_markdown_style_errors.sh`](scripts/fix_markdown_style_errors.sh) to do markdown linting locally
[`.markdownlintignore`](.markdownlintignore)|Files ignored by the Markdown linter, use [`./scripts/fix_markdown_style_errors.sh`](scripts/fix_markdown_style_errors.sh) to do markdown linting locally

<!-- markdownlint-enable MD013 -->
