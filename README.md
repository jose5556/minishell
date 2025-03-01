<h1 align="center"> 
  🖥️ Minishell </h1>
  
<p align="center"> 
  <img alt="Code bytes" src="https://img.shields.io/github/languages/code-size/jose5556/minishell?color=lightblue" /> 
  <img alt="Code language count" src="https://img.shields.io/github/languages/count/jose5556/minishell?color=yellow" /> 
  <img alt="GitHub top language" src="https://img.shields.io/github/languages/top/jose5556/minishell?color=blue" /> 
  <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/jose5556/minishell?color=green" /> 
</p>

# 💡 About the project

Minishell is a project completed during my studies at School 42. The objective of this project is to create a simple shell that replicates the basic functionalities of a Unix shell, handling command execution, redirections, pipes, environment variables, and more.
🔍 Overview

Minishell is a minimalistic version of Bash, built from scratch in C. It features a command-line interface where users can execute built-in commands, external programs, and handle input/output redirections. The project also includes signal handling for process control and implements &&, ||, ; operators for logical execution flow.
Key Features

    Command execution: Supports built-in commands and external programs.
    Pipes (|): Enables chaining multiple commands together.
    Redirections (<, >, >>): Handles input/output manipulation.
    Environment variables ($VAR): Expands shell variables dynamically.
    Logical operators (&&, ||, ;): Supports complex command execution.
    Signal handling: Manages Ctrl+C, Ctrl+D, and Ctrl+\ for process control.

For more detailed information about the implementation, please refer to the project files and documentation.
🛠️ Usage
Requirements

The project is written in C and requires the cc compiler and the readline library.

To install readline on Linux:

$ sudo apt-get install libreadline-dev

Instructions

1. Compiling the program

To compile Minishell, run the following command in the project directory:

$ make

2. Running Minishell

After compiling, start the shell by running:

$ ./minishell

You will then enter an interactive shell session where you can execute commands like:

minishell$ echo "Hello, world!"
Hello, world!

Instructions

1. Compiling the program

To compile Minishell, run the following command in the project directory:

$ make

2. Running Minishell

After compiling, start the shell by running:

$ ./minishell

You will then enter an interactive shell session where you can execute commands like:

minishell$ echo "Hello, world!"
Hello, world!

minishell$ ls -l | grep .c > files.txt

3. Built-in Commands Minishell supports the following built-in commands:

    echo (with -n option)
    cd (change directory)
    pwd (print working directory)
    export (set environment variables)
    unset (remove environment variables)
    env (print all environment variables)
    exit (exit the shell)

📌 Note

Minishell is a learning project designed to deepen understanding of Unix system calls, process management, and command execution. It is not a full Bash replacement but replicates essential features.
Use Control + Shift + m to toggle the tab key moving focus. Alternatively, use esc then tab to move to the next interactive 
minishell$ ls -l | grep .c > files.txt

3. Built-in Commands Minishell supports the following built-in commands:

    echo (with -n option)
    cd (change directory)
    pwd (print working directory)
    export (set environment variables)
    unset (remove environment variables)
    env (print all environment variables)
    exit (exit the shell)

📌 Note

Minishell is a learning project designed to deepen understanding of Unix system calls, process management, and command execution. It is not a full Bash replacement but replicates essential features.
