***PIPEX***

Pipex is a project in Hive Helsinki (42 Network)'s curriculum. The task was to create a program that simulates how a pipe works in the terminal.

My program tries to mimic the behaviour of the zsh shell.

***I. How to install***

1. Clone the repository

2. Navigate inside the repository

3. Run the command "make bonus"

***II. How to use***

The idea behind the program is that it should replicate a command structure that, in the shell, would look like:

< file1 cmd1 | cmd2 > file2

(Meaning that the first command is executed having its input be redirected from the first file, and the output of this first command is sent through a pipe to be the output of the second command, the output of which is redirected to the second file. If the second file already existed, it will be truncated.)

The way pipex meant to be used is:

./pipex "file1" "cmd1" "cmd2" "file2"

in which case it will behave the same way as the above shell command.

The usage of heredoc was also implemented. In such a case, the terminal command being replicated is:

cmd1 << LIMITER | cmd2 >> file

(Meaning that the user will be asked to type in the text that shall be the input of the first command. LIMITER is a string that has to be typed to signal that the user is finished with giving the input (the last line has to be equal to LIMITER, not merely contain it). Then, the output of the first command is sent through a pipe to be the output of the second command, the output of which is redirected to the second file. If the second file already existed, it will be appended.)

To have pipex give the same result as the above shell command, it must be used as:

 ./pipex here_doc LIMITER cmd1 cmd2 file

***III. Limitations***

Has been developed on mac, and only tested on linux, additionally. It does not handle special characters such as \ $ or single/double quotes, etc. If the environmental variable PATH is unset, attempting to run a directory as if it were an executable does not give the same error message as zsh. Segmentation faults and bus errors are handled properly, but other signals are not.