# City of Thieves

<!-- markdownlint-disable MD013 --><!-- Badges cannot be split up over lines, hence will break 80 characters per line -->

[![Check links](https://github.com/richelbilderbeek/city_of_thieves/actions/workflows/check_links.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/city_of_thieves/actions/workflows/check_links.yaml)
[![Check Markdown](https://github.com/richelbilderbeek/city_of_thieves/actions/workflows/check_markdown.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/city_of_thieves/actions/workflows/check_markdown.yaml)
[![Check spelling](https://github.com/richelbilderbeek/city_of_thieves/actions/workflows/check_spelling.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/city_of_thieves/actions/workflows/check_spelling.yaml)
[![Create the Zensical website](https://github.com/richelbilderbeek/city_of_thieves/actions/workflows/create_zensical_website.yaml/badge.svg?branch=main)](https://github.com/richelbilderbeek/city_of_thieves/actions/workflows/create_zensical_website.yaml)
[![codecov.io](https://codecov.io/github/richelbilderbeek/city_of_thieves/coverage.svg?branch=main)](https://codecov.io/github/richelbilderbeek/city_of_thieves/branch/main)

<!-- markdownlint-enable MD013 -->

- [Go to the nicely rendered site](https://richelbilderbeek.github.io/city_of_thieves/)

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
