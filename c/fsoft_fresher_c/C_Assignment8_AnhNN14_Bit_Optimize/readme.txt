To clear certain bits, & with the inverse of the bits to be cleared. Then you can | in the bits you want.

In this case, you want to zero out the lower three bits (111 in binary or 7 in decimal), 
so we & with ~7 to clear those bits.

Bits = (Bits & ~7) | 1; // set lower three bits of Bits to 001

32 bits data PORT
------------------------
|	2	|	15	|	15	|
------------------------

MASK = ~(0b11<<30) = 0b001_______________1
PORT = ((x & 0b11) << 30 ) | (MASK & PORT); // ghi gia tri x bat ky vao 2 bit dau, ko anh huong den cac bit khac.

// BT1: ghi gia tri x vao 15 bit giua?
// tao mask cua 15 bit giua
// 15 bit giua --> 7FFF
MASK = ~(0x7FFF<<15)
PORT = (PORT & ~0x7FFF) | x
PORT = ((x & 0x7FFF) << 15) | (MASK & PORT)

// BT2: ghi gia tri x vao 15 bit cuoi? (do nam o bit cuoi, sat 0 --> ko phai dich bit nua)
MASK = ~(0x7FFF)
PORT = (x & 0x7FFF) | (MASK & PORT)

all text that begins with # --> available at compiling time.
------------------------------------------------------------------------
Optimization in C
Trong vong lap for, neu phai goi lien tuc 1 bien nao do de tinh di tinh lai --> put in temp.