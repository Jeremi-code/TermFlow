## Description

This C++ project provides a simple terminal-based code launcher that integrates with the fzf fuzzy finder. The application allows users to quickly navigate and open projects from a specified directory using the Visual Studio Code. Additionally, it maintains a list of recently opened projects, displayed at the bottom of the fzf interface for easy access.

## Features

- Launch Visual Studio Code for selected projects.
- Utilizes fzf for a fast and interactive project selection.
- Keeps track of the most recently opened projects.
- Supports both manual selection and opening from the recent projects list.

## Usage

- Run the executable without any arguments to interactively select a project using fzf.
- Use the -r flag to open a project from the recent projects list.

## Dependencies

1. C++ Standard Library
2. fzf (needs to be installed separately)
3. fzf can be installed from scoop (command line package manager )

## Instructions

1. Install scoop by using iwr -useb get.scoop.sh | iex command
2. Install fzf from scoop using scoop install fzf
3. Clone TermFlow into your computer
4. Make sure you create a file for storing the recently opened projects and adjust the directory of the file in the code
5. Compile the source code with c++ compiler with the favourite name of yours
6. Add the directory of the compiled file in enviornment variable
7. Run the executable with the name of the compiled file without any arguments to interactively select a project using fzf
8. Use the -r flag to open a project from the recent projects list

