
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


int str_compare(const char *str1, const char *str2) {

	while (*str1 && (*str1 == *str2)) {

		str1++;
		str2++;
	}
	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

void clear_buffer(char *buf, int size) {

	for (int i = 0; i < size; i++) {

		buf[1] = 0;
	}
}


void kernel_main(void) {
    char *video_memory = (char *) 0xB8000;
    
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = 0x07;
    }

    char input_buffer[64];
    clear_buffer(input_buffer, 64);
    int buffer_idx = 0;

    const char *prompt = "COS> ";
    int cursor_pos = 0;
    
    int p = 0;
    while (prompt[p] != '\0') {
        video_memory[cursor_pos * 2] = prompt[p];
        video_memory[cursor_pos * 2 + 1] = 0x0A; 
	cursor_pos++;
        p++;
    }

    unsigned char last_scancode = 0;

    while (1) {
        if (inb(0x64) & 1) {
            unsigned char scancode = inb(0x60);

            if (scancode < 0x80 && scancode != last_scancode) {
                unsigned char ascii = keyboard_map[scancode];

                if (ascii != 0) {
                    
                    if (ascii == '\n') {
                        input_buffer[buffer_idx] = '\0'; 

                        cursor_pos = ((cursor_pos / 80) + 1) * 80;

                        if (str_compare(input_buffer, "info") == 0) {
                            const char *info_msg = "CompactOS v0.1 - Made by 1Sqware1 for fun & portfolio.";
                            int m = 0;
                            while (info_msg[m] != '\0') {
                                video_memory[cursor_pos * 2] = info_msg[m];
                                video_memory[cursor_pos * 2 + 1] = 0x0E;
                                cursor_pos++;
                                m++;
                            }
                        } 
                        else if (buffer_idx > 0) {
                            const char *err_msg = "Unknown command. Try: info";
                            int m = 0;
                            while (err_msg[m] != '\0') {
                                video_memory[cursor_pos * 2] = err_msg[m];
                                video_memory[cursor_pos * 2 + 1] = 0x0C;
                                cursor_pos++;
                                m++;
                            }
                        }

                        cursor_pos = ((cursor_pos / 80) + 1) * 80;

                        clear_buffer(input_buffer, 64);
                        buffer_idx = 0;

                        p = 0;
                        while (prompt[p] != '\0') {
                            video_memory[cursor_pos * 2] = prompt[p];
                            video_memory[cursor_pos * 2 + 1] = 0x0A;
                            cursor_pos++;
                            p++;
                        }
                    } 
                    else {
                        if (buffer_idx < 63) {
                            input_buffer[buffer_idx] = ascii; 
                            buffer_idx++;

                            video_memory[cursor_pos * 2] = ascii; 
                            video_memory[cursor_pos * 2 + 1] = 0x0F; 
                            cursor_pos++;
                        }
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

