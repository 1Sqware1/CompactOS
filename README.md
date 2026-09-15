## CompactOS
CompactOS - simple OS written on nasm, C. Just for my portfolio and fun :)
Just simple commands, games, PC recovery (maybe...?) — and nothing else.

## How it works?
asm (bootloader), C (kernel), C++ (utilities).

## What is this for?
for my portfolio and for fun (and to kill boredom). 👀

## How to get Bin? (for qemu)
**step 1:** clone this repo.

**step 2:** run ```make```.

**step 3:** ```qemu-system-i386 -kernel kernel.bin```.


## Roadmap

- [x] Write Hello World on C kernel.
- [x] Added Makefile.
- [x] Added Simple Keyboard Driver. 
- [ ] Write first commands: `help`, `reboot`, `echo`, `info`. (10% done)
- [ ] Write driver for FAT32.
- [ ] Make text editor (like nano/vim).
- [ ] Connect the bootloader to GRUB (create .iso image).
- [ ] ??? (The roadmap will be updated).

## future plans for this project
I don't know if there's any point in updating it after I've added everything I wanted to. It's not a Linux or Windows equivalent; it's just a hobby of mine, as I mentioned earlier.
