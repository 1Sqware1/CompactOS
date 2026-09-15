
unsigned char inb(unsigned short port) {
	unsigned char result;
	__asm__ __volatile__("inb %1, %0" : "=a"(result) : "Nd"(port));
	return result;

}

void outb(unsigned short port, unsigned char data) {

	__asm__ __volatile__("outb %0, %1" : : "a"(data), "Nd"(port));
}


unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,
 '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, '*',   0, ' '
};


void kernel_main(void) {
    char *video_memory = (char *) 0xB8000;
    
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = 0x07;
    }

    const char *welcome = "CompactOS v0.1.";
    int i = 0;
    while (welcome[i] != '\0') {
        video_memory[i * 2] = welcome[i];
        video_memory[i * 2 + 1] = 0x0A; 
        i++;
    }

    int cursor_pos = 80 * 2; 
    unsigned char last_scancode = 0;

    while (1) {
        if (inb(0x64) & 1) {
            unsigned char scancode = inb(0x60); 

            if (scancode < 0x80 && scancode != last_scancode) {
                
                unsigned char ascii = keyboard_map[scancode]; 

               if (ascii != 0) { 
    
    if (ascii == '\n') {
        cursor_pos = ((cursor_pos / 80) + 1) * 80;
    } 
    else {
        video_memory[cursor_pos * 2] = ascii;       
        video_memory[cursor_pos * 2 + 1] = 0x0F;   
        cursor_pos++;                              
    }

}

                
                last_scancode = scancode; 
            } 
            else if (scancode >= 0x80) {
                last_scancode = 0; 
            }
        }
    }
}

