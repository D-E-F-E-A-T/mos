momos
=====

#### A little x86 OS for fun.

[PIT Frequency too high in Bochs Problem.](http://forum.osdev.org/viewtopic.php?f=1&t=27574)

No memory management or well linking ? just place keyboard mapping in a fixed memory block which defined at file keyboard.h.

Floppy reading just let cylinder 0 - 79 like a flat mode, no need to set cylinder and just let it be 0. Sector value will calculate automatically.