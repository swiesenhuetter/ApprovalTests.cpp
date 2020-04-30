<a id="top"></a>

# Contributing to ApprovalTests.cpp


toc



## Contributing - pairing and pull requests

The default way to add to most repositories is to fork and then create a pull-request.

This is **NOT** the default way to contribute to Approval Tests!

If you have something that you would like Approval Tests to have, including a bug you would like removed, we suggest you set up a pairing session (usually Skype or Facetime) with either [Llewellyn](mailto:llewellyn.falco@gmail.com) or [Clare](mailto:github@cfmacrae.fastmail.co.uk) or both.

A typical session lasts between 60 to 90 minutes. We do the work directly on master, on our own machines, with screen-sharing, and commit and push the results throughout the session. This results in quicker, higher-quality work. It gives us a better understanding of how people are using Approval Tests and the problems they encounter with it, and these sessions are also quite fun.

We use github's "co-author" feature, so everyone in the pairing session gets credit for the work. Virtually this entire project has been developed in this way, and is stronger for it.

Example co-author text, for use if not using the GitHub Desktop application:

```
Co-Authored-By: Llewellyn Falco <isidore@users.noreply.github.com>
```

We use [Arlo's Commit Notation](https://github.com/RefactoringCombos/ArlosCommitNotation) to prefix most commits, to indicate their level of risk.

### Definition of Done

*Note: Reminder for Clare and Llewellyn*

* [ ] Tests
* [ ] Documentation
    * [ ] Sample code
    * [ ] Copy+pastable template (if appropriate)
    * [ ] A link on [Features](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Features.md#top)
    * [ ] A link on [build/relnotes_x.y.z.md](https://github.com/approvals/ApprovalTests.cpp/blob/master/build/relnotes_x.y.z.md)
    * [ ] Links on other appropriate places
* [ ] Check the [Dashboard](https://github.com/claremacrae/dashboard#top) (after pushing)
* [ ] Retrospective (as an experiment) on what we learned from the work

## Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](/CODE_OF_CONDUCT.md#top). By participating in this project you agree to abide by its terms.

## Formatting Code

If possible, please configure your editor to use this repository's [.clang-format](https://github.com/approvals/ApprovalTests.cpp/blob/master/.clang-format) file.

Instructions for this are available:

* CLion:
    * Settings/Preferences | Editor | Code Style | Turn on "Enable ClangFormat with clangd server" checkbox.
    * More information: [ClangFormat as Alternative Formatter](https://www.jetbrains.com/help/clion/clangformat-as-alternative-formatter.html)

There is a script to apply clang-format to the whole project: [scripts/reformat_code.sh](https://github.com/approvals/ApprovalTests.cpp/blob/master/scripts/reformat_code.sh).

We have a CI job called `clang-format` that checks for code not correctly formatted: [.github/workflows/github_actions_build.yml](https://github.com/approvals/ApprovalTests.cpp/blob/master/.github/workflows/github_actions_build.yml).

## Updating the simulated single-header

After adding new header files to the library, we need to update [ApprovalTests/ApprovalTests.hpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/ApprovalTests.hpp).

This is done by running [scripts/create_simulated_single_header.sh](https://github.com/approvals/ApprovalTests.cpp/blob/master/scripts/create_simulated_single_header.sh):

```bash
cd ApprovalTests.cpp
./scripts/create_simulated_single_header.sh
```

## Coding Patterns

See [Static variables for header-only releases](/doc/CodingPatterns.md#static-variables-for-header-only-releases).

## Documentation

We welcome improvements to the documentation! Here's how we manage the documentation files. 

### Future version numbers

To refer to the next release, use 'v.x.y.z', and make sure that there is a step to edit the file to update that text to the actual version number in the release scripts.

### Creating new pages

*Note: All the master Markdown pages in this project are called `mdsource/[something].source.md`*

**Using the template page**

If creating a new Markdown page, please make a copy of [doc/mdsource/TemplatePage.source.md](/doc/mdsource/TemplatePage.source.md#top).
This contains some boilerplate text which is tedious to create by hand.

The new file needs to be in a `mdsource` sub-directory.

**Creating multiple pages**

If creating multiple files, on Unix, you can use the script `doc/mdsource/create_page.sh`

```bash
cd doc/mdsource/
./create_page.sh TestingSingleObjects TestingContainers TestingCombinations
```

This won't overwrite existing files.
It will write out the text to paste in to other .md files, to correctly link to the new file. 

**For documentation files outside of doc**

If the new page will be outside of the [doc](/doc/) folder, delete the following lines at the end:

```markdown
---
   
[Back to User Guide](/doc/README.md#top)
```

### Internal links need to be absolute 

All references to other files in this project, such as hyperlinks and images, must specify the full path from the root of the repository. This will allow those links to work correctly in both the source and generated markdown files. Relative paths cannot work for both the source and the target file. 

For example, use this:

```markdown
* [this link will work everywhere](/doc/Reporters.md#top)
```

Not this:

```markdown
* [this link is wrong](doc/Reporters.md#top)
```

And not this:

```markdown
* [this link is wrong](Reporters.md#top)
```

### Adding code and file samples

We use Simon Cropp's [MarkdownSnippets](https://github.com/SimonCropp/MarkdownSnippets) tool to embed source code and other files in Markdown pages.

**How it works:**

* Call the source file `[something].source.md`.
* Make sure it is in a `mdsource` directory
* See the [MarkdownSnippets](https://github.com/SimonCropp/MarkdownSnippets) documentation for how to:
    * annotate snippets of source code, 
    * reference the snippets in documentation.
* Run  `run_markdown_templates.sh` **before commit**, every time a `.source.md` file is updated
    * See [run_markdown_templates.sh](/run_markdown_templates.sh).
    * This will update the tables of contents and the machine-generated `[something].md` files.
    * If this does not work, see that script for how to install the tools it uses

#### Managing CMake code samples

The repository [claremacrae/ApprovalTests.cpp.CMakeSamples](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples) has some sample CMake projects for various development scenarios.

I'm exploring ways of embedding some CMake files from that repo in to [CMake Integration](/doc/CMakeIntegration.md#top) - see [MarkdownSnippets #157](https://github.com/SimonCropp/MarkdownSnippets/issues/157).

For now, I've used [claremacrae/ApprovalTests.cpp.CMakeSamples/create_markdown.py](
https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/master/create_markdown.py) to convert the interesting CMake files to Markdown, and copy them to [doc/mdsource/](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/mdsource) with file names `inc_*.include.md`.

### Checking the documentation

#### Automated checking of links in documentation

There is a "markdown-link-check" github workflow that checks for broken links all in the Markdown files. It checks for missing file names, but will not detect missing anchors.

* It runs the script [scripts/check_links.sh](/scripts/check_links.sh) ...
* ... which uses the configuration file [mlc_config.json](/mlc_config.json) ...
* ... and runs [tcort's markdown-link-check](https://github.com/tcort/markdown-link-check)

If there are any failures, the output is slightly verbose to look through - you have to find lines beginning `[*]`, but I think that these will be sufficiently few and far between that this is good enough.

#### Other checks of documentation

The script [fix_markdown.sh](/fix_markdown.sh) can be used to do some checks of the Markdown documentation files.

## Releases

* Everything for releases is in [the build directory](/build/)
* There's more information in [How To Release](/build/HowToRelease.md#top)

## Running shell scripts in cygwin

To run `.sh` in cygwin on Windows, add these lines to `~/.bash_profile`, and then re-start cygwin:

```bash
export SHELLOPTS
set -o igncr
```

[Credit](https://ptolemy.berkeley.edu/projects/chess/softdevel/faq/5.html)

---

[Back to User Guide](/doc/README.md#top)
