#pragma once

#include <def.h>

uchar  insb(ushort port);
ushort insw(ushort port);

void outb(ushort port, uchar val);
void outw(ushort port, ushort val);