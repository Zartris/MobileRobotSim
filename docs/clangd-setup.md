# clangd Setup Guide for MobileRobotSim

This document outlines the clangd integration for the MobileRobotSim project.

## Overview

[clangd](https://clangd.llvm.org/) is a language server that provides rich C++ language features to your editor. It offers several advantages over the Microsoft C++ IntelliSense:

- Faster and more accurate code completion
- Better navigation capabilities
- Real-time error detection
- More precise refactoring tools
- Native support for clang-tidy integration

## Configuration Files

The following files have been set up to work with clangd:

### `config/clangd.config`

This file configures clangd's behavior, including:
- Compiler flags
- Diagnostic settings
- clang-tidy integration
- Formatting preferences
- Code navigation features

### `config/clang-format.config`

Defines the code formatting style used by both clangd and the clang-format tool.

### `compile_commands.json`

Generated in the build directory and copied to the project root by the `scripts/generate_compile_commands.sh` script. This file tells clangd exactly how each source file should be compiled, ensuring accurate code intelligence.

## VSCode Configuration

The `.devcontainer/devcontainer.json` has been configured to:

1. Install and use the clangd extension
2. Disable the conflicting features from Microsoft's C++ extension
3. Configure clangd with optimal settings

## Using clangd

### Within VSCode Container

When using the configured development container, clangd will be automatically set up with all necessary extensions and settings.

### First-Time Setup

When starting the project for the first time (or after making significant changes to the build system):

1. Build the project to generate the initial compilation database:
   ```bash
   ./scripts/generate_compile_commands.sh
   ```

2. If you're using VSCode, the clangd extension should automatically pick up the compilation database and begin analyzing your code.

### Key Features to Try

- **Symbol Navigation**: Go to definition (F12), references (Shift+F12)
- **Intelligent Autocomplete**: Begin typing and view context-aware suggestions
- **Error Checking**: Live error diagnostics as you type
- **Code Actions**: Hover over underlined code for suggested fixes
- **Semantic Highlighting**: Better code coloring based on semantic understanding
- **Hover Documentation**: Move your cursor over symbols for detailed documentation

## Troubleshooting

If clangd doesn't seem to be working correctly:

1. **Check clangd status**: In VSCode, click on the clangd icon in the status bar for diagnostics
2. **Regenerate compile_commands.json**: Run `./scripts/generate_compile_commands.sh` again
3. **Restart clangd**: In VSCode, press Ctrl+Shift+P and select "clangd: Restart Language Server"
4. **Logs**: Check the Output panel in VSCode (View -> Output) and select "clangd" from the dropdown

## Performance Tips

- clangd maintains an index of your codebase to provide fast lookups. The first startup may be slower, but subsequent startups will be faster.
- If you have a large codebase, consider using a `.clangd-ignored` file to exclude non-essential directories from indexing.
- Use the "clangd: Check for Updates" command in VSCode to keep clangd up to date.
