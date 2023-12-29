/*
 * cmd.c
 *
 * Created: 26-11-2023 16:48:54
 *  Author: Mikael Ejberg Pedersen
 */ 

#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdio.h>
#include "cmd.h"

extern const __flash cmdlist_t __cmdtable_start;
extern const __flash cmdlist_t __cmdtable_end;

static void helpCmd(uint8_t argc, char *argv[])
{
    const __flash cmdlist_t  *p = &__cmdtable_start;

    while (p < &__cmdtable_end)
    {
        printf_P(PSTR("%-12S : %S\n"), p->name, p->help);
        p++;
    }
}

CMD(help, "This help");


void cmd_exec(uint8_t argc, char *argv[])
{
    const __flash cmdlist_t  *p = &__cmdtable_start;

    while (p < &__cmdtable_end)
    {
        if (!strcmp_P(argv[0], p->name))
        {
            p->func(argc, argv);
            return;
        }
        p++;
    }
    printf_P(PSTR("Command not found\n"));
}
