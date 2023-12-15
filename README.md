## Description

This C++ project provides a simple terminal-based code launcher that integrates with the fzf fuzzy finder. The application allows users to quickly navigate and open projects from a specified directory using the Visual Studio Code (code) command. Additionally, it maintains a list of recently opened projects, displayed at the bottom of the fzf interface for easy access.

## Features

Launch Visual Studio Code for selected projects.
Utilizes fzf for a fast and interactive project selection.
Keeps track of the most recently opened projects.
Supports both manual selection and opening from the recent projects list.

## Usage

Run the executable without any arguments to interactively select a project using fzf.
Use the -r flag to open a project from the recent projects list.

## Dependencies

C++ Standard Library
fzf (needs to be installed separately)

## Instructions

Run the executable without any arguments to interactively select a project using fzf.
Use the -r flag to open a project from the recent projects list.
Compile the source code using a C++ compiler.
Make sure the fzf utility is installed on your system.
Run the executable to launch projects interactively.
