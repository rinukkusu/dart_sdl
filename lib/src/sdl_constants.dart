// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

// Misc
const int SDL_ENABLE = 1;
const int SDL_DISABLE = 0;
const int SDL_QUERY = -1;

// Subsystem Initialization
const int SDL_INIT_TIMER = 1;
const int SDL_INIT_AUDIO = 16;
const int SDL_INIT_VIDEO = 32;

// Window Initialization
const int SDL_WINDOW_FULLSCREEN = 1;
const int SDL_WINDOW_OPENGL = 1 << 1;
const int SDL_WINDOW_SHOWN = 1 << 2;
const int SDL_WINDOW_HIDDEN = 1 << 3;
const int SDL_WINDOW_BORDERLESS = 1 << 4;
const int SDL_WINDOW_RESIZABLE = 1 << 5;
const int SDL_WINDOW_MINIMIZED = 1 << 6;
const int SDL_WINDOW_MAXIMIZED = 1 << 7;
const int SDL_WINDOW_INPUT_GRABBED = 1 << 8;
const int SDL_WINDOW_INPUT_FOCUS = 1 << 9;
const int SDL_WINDOW_MOUSE_FOCUS = 1 << 10;
const int SDL_WINDOW_FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN | (1 << 12);
const int SDL_WINDOW_ALLOW_HIGHDPI = 1 << 13;
const int SDL_WINDOW_MOUSE_CAPTURE = 1 << 14;
const int SDL_WINDOW_ALWAYS_ON_TOP = 1 << 15;
const int SDL_WINDOW_SKIP_TASKBAR = 1 << 16;
const int SDL_WINDOW_UTILITY = 1 << 17;
const int SDL_WINDOW_TOOLTIP = 1 << 18;
const int SDL_WINDOW_POPUP_MENU = 1 << 19;

// Events
const int SDL_QUIT = 256;
const int SDL_WINDOWEVENT = 512;
const int SDL_KEYDOWN = 768;
const int SDL_KEYUP = 769;
const int SDL_MOUSEMOTION = 1024;
const int SDL_MOUSEBUTTONDOWN = 1025;
const int SDL_MOUSEBUTTONUP = 1026;
const int SDL_MOUSEWHEEL = 1027;
const int SDL_DROPFILE = 4096;
const int SDL_DROPTEXT = 4097;
const int SDL_DROPBEGIN = 4098;
const int SDL_DROPCOMPLETE = 4099;

// SDL_Image
const int IMG_INIT_JPG = 1;
const int IMG_INIT_PNG = 1 << 1;
const int IMG_INIT_TIF = 1 << 2;
const int IMG_INIT_WEBP = 1 << 3;