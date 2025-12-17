# EnseaSH - Linux Micro Shell Mini Project
EnseaSH is a minimal Unix shell developed as part of an academic lab project.
It allows users to execute system commands while displaying exit codes, signals, and execution times for each program.

The project has strict low-level programming constraints, for example, the use of `printf` and `system` is prohibited.

## Implemented Features
- Welcome message and prompt
- REPL loop (Read-Eval-Print Loop)
  - Read user input
  - Execute commands
  - Return to prompt
- Shell exit
- Exit status and signal display
- Execution time measurement
- Commands with arguments
- Input/Output redirections
  - `<` for stdin
  - `>` for stdout

Here is a demonstration of the different features:
```shell
Welcome to enseash!
To exit, type 'exit'
enseash % whatever                          
whatever: No such file or directory
enseash [exit:1|1ms] % sort < names.txt > sorted_names.txt
enseash [exit:0|2ms] % ls
build  demo.txt  include   names.txt  sorted_names.txt
case.  enseash   Makefile  README.md  src
enseash [exit:0|3ms] % rm names.txt sorted_names.txt
enseash [exit:0|2ms] % sleep 100000
enseash [sign:9|10592ms] % exit
see you soon ;)
```
