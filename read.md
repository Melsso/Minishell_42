# Custom Shell Project

## Overview

This project is a simple implementation of a command-line shell in C, inspired by Bash. The custom shell provides basic functionality such as executing commands, handling built-in commands, and supporting I/O redirection.

## Features

- **Command Execution:** The shell can execute external commands by forking a new process and using `execve`.
- **Built-in Commands:** Supports built-in commands like `cd`, `exit`, `export` etc.
- **I/O Redirection:** Allows redirection of standard input and output using `<`, `>`, `<<`, `>>` operators.
- **Pipelines:** Supports basic command pipelines using the `|` operator.

## Usage

1. **Compilation:**
   make
   ./minishell
   enjoy!