# TicTacToe

Simple TicTacToe game in command-line or GUI.
I did this to practise my C, not to be rusty.

## Overview

### Command Line
![Command Line Overview](img/cli_overview_1.png)

![Command Line Overview](img/cli_overview_2.png)

### Graphical

*not yet*

## Getting started

### Compiling

```bash
gcc -o tictactoe tictactoe.c
```

### Running in Command Line
```bash
./tictactoe cli
```

### Running in Graphical
```bash
./tictactoe gui
```


## Memo

### Debug with GDB :
```bash
gcc -o tictactoe -g tictactoe.c
gdb -q ./tictactoe
(gdb) run cli
```

### Display all warnings as errors :
Correct all these warnings !
```bash
gcc -o tictactoe -Wall -Wextra -Werror --std=c99 tictactoe.c
```
