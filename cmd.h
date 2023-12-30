/*
 * cmd.h
 *
 * Created: 26-11-2023 16:48:42
 *  Author: Mikael Ejberg Pedersen
 */

#ifndef CMD_H_
#define CMD_H_

#include <stdint.h>

typedef void    (*cmdfunc_t)(uint8_t argc, char *argv[]);

typedef struct
{
    const __flash char *name;
    const __flash char *help;
    const cmdfunc_t func;
} cmdlist_t;

#define CMD(cmdname, cmdhelp) \
static const __flash char cmdname##Name[] = #cmdname; \
static const __flash char cmdname##Help[] = #cmdhelp; \
static const cmdlist_t cmdname##CmdTableEntry \
__attribute__((used, section(".cmdtable." #cmdname))) = { \
    .name = cmdname##Name, \
    .help = cmdname##Help, \
    .func = cmdname##Cmd \
};

/**
 * Find command in list and execute it.
 *
 * @param argc Argument count. Number of arguments in argv.
 * @param argv Argument vector. Array of argument ptrs.
 */
extern void     cmd_exec(uint8_t argc, char *argv[]);

/**
 * Split command line into argc/argv and call cmd_exec.
 *
 * @param cmd Command line.
 */
extern void     cmd_split_exec(char *cmd);

#endif /* CMD_H_ */
