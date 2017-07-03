# FT_SELECT - @42Born2Code

A robust file browser and manager in the terminal.

## About

ft_select is the third project of the Unix branch at 42. The goal for this project is to learn more about screen oriented programs using termcap/terminfo libraries in the C programming language. It's originally just an argument viewer in the terminal but I decided to take it one step further and gave it browsing capabilities on the file system.

The main goal, however, is to build my own functional shell. Something like `zsh` and `bash`, this is what the next project at my school is about and ft_select is just a small part of it.

## How to use it

### Requirements

To be able to build and run this program, you'll need:

* A Unix system
* GNU make (v3.81)
* GCC (v4.2.1)

Those are the versions used during development.

### Building

1. Download/Clone this repo

		git clone https://github.com/r4meau/ft_select

2. `cd` into the root directory and run `make`

		cd ft_select
		make

### Running

A basic usage would involve at least one argument:

 	./ft_select hello

## Features

* If you pass a list of arguments to the program it gets displayed in your terminal.
* You can move through the list using arrows.
* One or more choices can be selected or un-selected with the `space` key. With
each selection, the cursor will automatically position itself on the next element.
* You can validate the selection with the `return` key, the list of choices will
be sent back to the shell. This allows other programs to use the output of the program as their input. i.e: rm `./ft_select file1 file2 file3`
* Re-organizes the display on window resize or displays a blank screen if the list cannot fit the in window.
* Exits on `ESC` key
* Pressing the `delete` or `backspace` keys removes an element from the list. In Real mode (Read below), it will automatically delete the active element from the system if it's a valid file (no folders). So watch out!
* Colored output based on some supported file extensions.
* Pressing the keys `O` and `B` opens a valid folder and goes back to the parent root directory respectively.
* Handles interruption signals gracefully (ctrl + z, ctrl + c, kill, etc...)
* Restores the screen to what it was before clearing it.

## Acknowledgment

Thanks to all my peers at 42 who helped me finish this project in 3 days, most notably @cgerbaud and @gguiulfo.

Enjoy!
