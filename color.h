#pragma once

#include "libraries/concolors.h"

void color_init();
void fg_color(TerminalColor);
void bg_color(TerminalColor);
void color(TerminalColor, TerminalColor);
void color_reset();

void input_color();
void error_color();