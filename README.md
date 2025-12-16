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
- Commands with argyments
- Input/Output redirections
  - `<` for stdin
  - `>` for stdout
