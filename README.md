<h1 align="center"> 
  🖥️ Minishell </h1>
  
<p align="center"> 
  <img alt="Code bytes" src="https://img.shields.io/github/languages/code-size/jose5556/minishell?color=lightblue" /> 
  <img alt="Code language" src="https://img.shields.io/github/languages/count/jose5556/minishell?color=yellow" /> 
  <img alt="Top language" src="https://img.shields.io/github/languages/top/jose5556/minishell?color=blue" /> 
  <img alt="Last commit" src="https://img.shields.io/github/last-commit/jose5556/minishell?color=green" />
</p>

# 💡 About the project

Minishell is a project completed during my studies at School 42. 
The objective of this project is to create a simple shell that replicates the basic functionalities of a Unix shell, handling command execution, redirections, pipes, environment variables, and more.

# 🔍 Overview

Minishell is a very small version of Bash, built from scratch in C. It features a command-line interface where users can execute built-in commands, external programs, and handle input/output redirections. The project also includes signal handling for process control.

For more detailed information about the implementation, see the project subject that is among the uploaded files.

# 🛠️ Usage

### Requirements

The project is written in C and requires the cc compiler and the readline library.

### Instructions

1. Compiling the program

To compile Minishell, run the following command in the project directory:

```shell
$ make
```

2. Running Minishell

After compiling, start the shell by running:

```shell
$ ./minishell
```

You will then enter an interactive shell session where you can execute commands like:

```shell
$ echo "Hello, world!"
$ Hello, world!
```
<br>

```shell
$ ls -l | grep .c > files.txt
```

3. Built-in Commands Minishell supports:

    <h4>echo (with -n option)</h4>
    <h4>cd (change directory)</h4>
    <h4>pwd (print working directory)</h4>
    <h4>export (set environment variables)</h4>
    <h4>unset (remove environment variables)</h4>
    <h4>env (print all environment variables)</h4>
    <h4>exit (exit the shell)</h4>

# 📌 Note

<h4>
  This project requires the readline library. If, for some unknown reason, an error appears when compiling the
  project, you can resolve it with the following command:
</h4>

```shell
$ sudo apt-get install libreadline-dev
```
