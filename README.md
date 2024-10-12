# 42 Minishell Project

## Overview

The 42 Minishell project aims to create a simple Unix shell using the C programming language. This project provides hands-on experience with process management, command execution, and the fundamentals of shell behavior.

## Features

- **Command Execution**: Execute built-in commands and external programs.
- **Piping**: Support for pipes to connect the output of one command to the input of another.
- **Redirection**: Handle input and output redirection using `<`, `>`, and `>>`.
- **Environment Variables**: Access and modify environment variables.
- **Signal Handling**: Properly handle signals like `SIGINT` and `SIGQUIT`.
- **Tab Completion**: (Optional) Implement basic tab completion for commands.

## Requirements

- C Compiler: Ensure you have a C compiler installed (e.g., `gcc` or `clang`).
- Unix Environment: This project should be developed and tested in a Unix-like environment (Linux or macOS).

## Installation

To install the 42 Minishell, follow these steps:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Melsso/Minishell_42.git
   cd Minishell_42
   ```
2. **Compile the Program**:
	```bash
	make
	```
3. **Run the Shell**:
	```bash
	./minishell
	```
## Usage

1. **Launching Minishell**: 
   - Open your terminal.
   - Navigate to the directory where the Minishell is located.
   - Run the program with:
     ```bash
     ./minishell
     ```
2. **Executing Commands**: 
   - Type your command and press `Enter`. 
   - For example:
     ```bash
     ls -l
     ```
3. **Using Pipes**: 
   - You can chain commands using pipes:
     ```bash
     ls -l | grep ".c"
     ```
4. **Redirection**:
   - Redirect input and output:
     ```bash
     echo "Hello, World!" > hello.txt
     cat < hello.txt
     ```
5. **Environment Variables**: 
   - You can access and set environment variables:
     ```bash
     export MY_VAR="some_value"
     echo $MY_VAR
     ```

## Contributing

We welcome contributions to the 42 Minishell project! To contribute, please follow these guidelines:

1. **Fork the Repository**: Click on the "Fork" button on the top right corner of the repository page to create your own copy of the project.
2. **Create a New Branch**: Use a descriptive name for your branch. For example:
	```bash
	git checkout -b feature/your-feature-name
	```
3. **Make Your Changes**: Implement your feature or bug fix. Ensure that your code adheres to the project's coding standards.
4. **Commit Your Changes**: Write clear, concise commit messages that describe your changes:
	```bash
	git commit -m "Add feature or fix bug description"
	```
5. **Push to Your Forked Repository**:
	```bash
	git push origin feature/your-feature-name
	```

6. **Open a Pull Request**: Go to the original repository and click on the "New Pull Request" button to submit your changes for review.

## License

This project is licensed under the MIT License.
## Contact

For questions, suggestions, or feedback, please contact us at [your-email@example.com].

## Acknowledgments

- Thanks to the contributors and the 42 community for their support and feedback.
- Inspired by the principles of open communication and collaboration.
