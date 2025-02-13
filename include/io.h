#pragma once

#include <def.h>

u8  inb(u16 port);
u16 inw(u16 port);

void outb(u16 port, u8 val);
void outw(u16 port, u16 val);