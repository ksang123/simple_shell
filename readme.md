# ByteForge - a simple shell
- a linux like - multiplatform shell implementation

## goals

### basic shell commands
- implement the basic bash commands like `cd`, `echo`, `history`

### default commands
- allow the user to run default shell commands 

### external commands
- implement external commands using a /bin in the `/ByteX`
- keep the external commands multiplatform by using C code.
- the command will be compiled once when first run.
- the compilation will be performed using the machine's C compiler.
- detect the machine's C compiler and save it to a file
- (install a C compiler for the user?)
- `compile bin` command that will compile all commands at once

### permission management
- the shell will be able to run without super permissions
- the shell will be able to perform super commands using a custom `sudo`

## extreme features
- those features will prob not be added, but I would like to consider them:
- auto command suggestion / completion? (while typing) 
- command correction (after trying to use a command that doesn't exist)


## todo

### basic shell behavior
- ANSICON for windows
- implement the shell UI
- implement working directory

### basic shell commands
- implement: `echo`, `cd`, `pwd`, `ls`, `mkdir`, `touch`, `time`
- `rmdir`, `rm` - will require confirmation
- `alias`, `history` - requires a file for saving information
- `grep` implementing efficiently would be challenging
- `find` to search for files
- `byteforge` - print a cool ascii logo and some details
- `bash` to run default OS commands

### default commands
- `bash` to run default OS commands - counts as a basic command
- allow the user to run default shell commands
- permission management for default commands

### external commands
- find the user's C compiler (offer to install gcc?)
- implement the /ByteX directory
- print files using `cat`
- implement a text editor like `nano`
- text files comparing using `diff`
- `wc` Count lines, words, and characters in a file.