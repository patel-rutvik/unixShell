# Unix Shell
A unix shell to provide a user interface to access the operating system services. This was made to learn about systems programming, multiple processes, resource management and process communication.

See the project in action [here](https://youtu.be/jlrRjN2nMzs)!
## Built-in Commands
`jobs` : displays the status of all running processes spawned by the shell

`exit` : ends the execution of the shell, after waiting for all processes to finish

`kill <int>` : kill process with the specificied pid

`resume <int>` : resume the execution of a *suspended* process

`sleep <int>` : sleep for <int> seconds

`suspend <int>` : suspend the execution of the specified process

`wait <int>` : wait until the specified process has completed execution

## Command Syntax
If none of the built-in commands are to be executed, the shell will execute any regular shell command!

`<cmd> <args>*` : spawns a process to execute the command `<cmd>` with 0 or more arguments `<args>`

## Special Arguments
`&` : If used, must be the last argument and suggests that the user wants to run this command in the *background*

`< filename` : a file name to be used for *input*

`> filename` : a file name to be used for *output*

## Building the Shell
To **build** the project, navigate to the source directory in your terminal shell, and use the following command:
```
make && ./unixShell
```
