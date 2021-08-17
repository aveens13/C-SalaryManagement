#include "color.h"

static TerminalInfo *ti;

void color_init() {
    ti = console_init();
}

void fg_color(TerminalColor fg) {
    console_set_fg_color(ti, fg);
}

void bg_color(TerminalColor bg) {
    console_set_bg_color(ti, bg);
}

void color(TerminalColor fg, TerminalColor bg) {
    console_set_colors(ti, fg, bg);
}

void color_reset() {
    console_reset_colors(ti);
}

void input_color() {
    fg_color(COLOR_BLUE | COLOR_BRIGHT);
}

void error_color() {
    fg_color(COLOR_RED | COLOR_BRIGHT);
}
