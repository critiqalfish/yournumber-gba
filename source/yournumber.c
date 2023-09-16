#include <tonc.h>

void draw_selector(int index, COLOR clr) {
	if (index > -1 && index < 11) {
		m3_rect(1 + (index * 16), 142, 15 + (index * 16), 144, clr);
		m3_rect(1 + (index * 16), 144, 3 + (index * 16), 147, clr);
		m3_rect(13 + (index * 16), 144, 15 + (index * 16), 147, clr);

		m3_rect(1 + (index * 16), 155, 15 + (index * 16), 157, clr);
		m3_rect(1 + (index * 16), 151, 3 + (index * 16), 156, clr);
		m3_rect(13 + (index * 16), 151, 15 + (index * 16), 156, clr);
	}
	else if (index == 11) {
		m3_rect(175, 142, 213, 144, clr);
		m3_rect(175, 144, 177, 147, clr);
		m3_rect(211, 144, 213, 147, clr);

		m3_rect(175, 155, 213, 157, clr);
		m3_rect(175, 151, 177, 156, clr);
		m3_rect(211, 151, 213, 156, clr);
	}
	else if (index == 12) {
		m3_rect(213, 142, 235, 144, clr);
		m3_rect(213, 144, 215, 147, clr);
		m3_rect(233, 144, 235, 147, clr);

		m3_rect(213, 155, 235, 157, clr);
		m3_rect(213, 151, 215, 156, clr);
		m3_rect(233, 151, 235, 156, clr);
	}
}

void thank_you() {
	int scale = 5;
	int heart[9][9] = {
		{0x7FFF, 0x7FFF, 0x0000, 0x0000, 0x7FFF, 0x0000, 0x0000, 0x7FFF, 0x7FFF},
		{0x7FFF, 0x0000, 0x001F, 0x001F, 0x0000, 0x001F, 0x001F, 0x0000, 0x7FFF},
		{0x0000, 0x001F, 0x7FFF, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000},
		{0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0000},
		{0x0000, 0x0010, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0010, 0x0000},
		{0x7FFF, 0x0000, 0x0010, 0x001F, 0x001F, 0x001F, 0x0010, 0x0000, 0x7FFF},
		{0x7FFF, 0x7FFF, 0x0000, 0x0010, 0x001F, 0x0010, 0x0000, 0x7FFF, 0x7FFF},
		{0x7FFF, 0x7FFF, 0x7FFF, 0x0000, 0x0010, 0x0000, 0x7FFF, 0x7FFF, 0x7FFF},
		{0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x0000, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF}
	};

	m3_puts(100, 50, "THANK", CLR_BLACK);
	m3_puts(108, 62, "YOU", CLR_BLACK);


	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			m3_rect(97 + (c * scale), 74 + (r * scale), 97 + scale + (c * scale), 74 + scale + (r * scale), heart[r][c]);
		}
	}
}

int main()
{	
	int cursor = 0;
	int selector = 0;
	const char * chars = "+0123456789";

	REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;
	
	txt_init_std();

	// clear
	m3_fill(CLR_WHITE);

	// title
	m3_puts(7, 6, "YOUR NUMBER PLS (i said pls)", CLR_BLACK);

	// number frame
	m3_frame(5, 18, 235, 33, CLR_BLACK);
	m3_frame(6, 19, 234, 32, CLR_BLACK);

	// dialboard separator
	m3_rect(0, 138, 240, 140, CLR_BLACK);

	// numbers
	for (int i = 0; i < 11; i++) {
		m3_putc(4 + (i * 16), 146, chars[i], CLR_BLACK);
	}

	// back and ok
	m3_puts(178, 146, "back", CLR_BLACK);
	m3_puts(216, 146, "OK", CLR_BLACK);

	// selection indicator
	draw_selector(selector, CLR_BLACK);

	// main loop
	while (1) {
		vid_vsync();
		key_poll();

		if (key_hit(KEY_LEFT)) {
			draw_selector(selector, CLR_WHITE);
			if (selector == 0) selector = 12;
			else selector--;
			draw_selector(selector, CLR_BLACK);
		}
		else if (key_hit(KEY_RIGHT)) {
			draw_selector(selector, CLR_WHITE);
			if (selector == 12) selector = 0;
			else selector++;
			draw_selector(selector, CLR_BLACK);
		}
		else if (key_hit(KEY_A)) {
			if (selector < 11 && cursor < 28) {
				m3_putc(8 + (cursor * 8), 22, chars[selector], CLR_BLACK);
				cursor++;
			}
			else if (selector == 11 && cursor > 0) {
				cursor--;
				m3_rect(8 + (cursor * 8), 22, 16 + (cursor * 8), 30, CLR_WHITE);
			}
			else if (selector == 12) {
				thank_you();
			}
		}
		else if (key_hit(KEY_SELECT)) {
			draw_selector(selector, CLR_WHITE);
			selector = 11;
			draw_selector(selector, CLR_BLACK);
		}
		else if (key_hit(KEY_START)) {
			draw_selector(selector, CLR_WHITE);
			selector = 12;
			draw_selector(selector, CLR_BLACK);
		}
	};

	return 0;
}