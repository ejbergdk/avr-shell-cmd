/* Linker script augmentation */

SECTIONS
{
  cmdtables :
  {
    PROVIDE (__cmdtable_start = .) ;
    *(SORT_BY_NAME(cmdtable*))
    PROVIDE (__cmdtable_end = .) ;
    KEEP(*(cmdtable*))
    . = ALIGN(2);
  }
}

INSERT AFTER .text
