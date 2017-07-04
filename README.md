# FT_SELECT - @42Born2Code

A robust file browser and manager in the terminal.

![](https://raw.githubusercontent.com/R4meau/ft_select/master/assets/main.gif)

## About

[ft_select](https://github.com/R4meau/ft_select/blob/master/ft_select.en.pdf) is the third project of the Unix branch at 42. The goal for this project is to learn more about screen oriented programs using termcap/terminfo libraries in the C programming language. It's originally just an argument viewer in the terminal but I decided to take it one step further and gave it browsing capabilities on the file system.

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
* Pressing the `delete` or `backspace` keys removes an element from the list. In Real mode (Read below), it will automatically delete the active element from the system if it's a valid file/folder. So watch out!
* Colored output based on some supported file extensions.
* Pressing the keys `O` and `B` opens a valid folder and goes back to the parent root directory respectively.
* Handles interruption signals gracefully (ctrl + z, ctrl + c, kill, etc...)
* Restores the screen to what it was before clearing it.
* No memory leaks
* Whole codebase is commented for easier browsing.

### Real mode

You can launch the program in real mode. In real mode, when you press `delete`/`backspace` on a valid file or folder, it will be deleted on the system too. So again, watch out! I'm not responsible for any loss of your files.


To run ft_select in real mode, use the flag `-r` or `--real`

	./ft_select -r I love 42

### TODO

* Add breadcrumb
* Press `H` to see hidden/dot files
* Add copy and move capabilities
* Even better error handling

## NOTES

* Don't mind the uneven tab widths, just set your editor's tab size to 4 (hard tabs, not soft) and it should be fine
* You might not like the fact that I'm not adding curly braces for some if statements, curly braces add extra lines, and my school has a coding standard (The Norme) that you must follow to succeed the projects, this standard imposes some rules like 25 lines function limits etc... Read more about it [here](https://github.com/R4meau/ft_select/blob/master/norme.en.pdf).
* I added a second branch called `original` which is the original code of the program before I started norming the code. It will lack some extra features that I didn't add back then. It's here to show me how I code initially and will help me see how much I improve over time.

### Resources

Here's a list of resources (in no particular order) I found useful to complete this project:

* [WikiBooks](https://en.wikibooks.org/wiki/Serial_Programming/termios)
* [Daemon Systems](https://www.daemon-systems.org/man/terminfo.5.html)
* [Cygwin](https://cygwin.com/ml/cygwin/2004-04/msg01158.html)

## Acknowledgment

Thanks to my peers at 42, Christophe Gerbaudo (@cgerbaud) and Giacomo Guiulfo (@gguiulfo) who helped me go faster on this project and gave me some great tips.

Enjoy!
