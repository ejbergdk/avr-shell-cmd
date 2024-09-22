# avr-shell-cmd
Small helper library for creating shell commands on an AVR, when using avr-gcc.
Requires adding an augmented linker script.

## Linker script augmentation
This repository includes an augmented linker script: `cmdtables.ld`. Tell the linker to augment the linker script with this file (use the -T command line option). In Atmel/Microchip Studio this is done in the project properties (Alt+F7), Toolchain, AVR/GNU Linker, Miscellaneous, Other Linker Flags. Add the line:
```
-T $(ProjectDir)\lib\avr-shell-cmd\cmdtables.ld
```
Change the path to match where you've included this repo.

If you don't use Atmel/Microchip Studio, add the linker option in your makefile.

## Using avr-shell-cmd
First, include the files here in your build. This repo can be included as a submodule.  
Then add the linker script as described above.

### Creating a shell command
Wherever you want a shell command, include cmd.h. Then make a static function with the command you want (name it the command followed by "Cmd"), and then put it in a CMD macro. Here is a command called "example":
```
static void exampleCmd(uint8_t argc, char *argv[])
{
    // Your command code goes here
}

CMD(example, "Put helptext here");
```
That is all that's needed.

### Executing a shell command
Collect input from a serial port (or anywhere else you want to expose a shell). Once a full line has been read, call *cmd_split_exec* with the line.
The correct command function will be called.

One command is already provided: *help*. It will print a list of all commands and their helptext.
