// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import 'dart-ext:sdl_extension';

num SDL_INIT_VIDEO = 32;
num SDL_WINDOW_OPENGL = 2;

bool SDL_Init(int flags) native "SDL_Init";
int SDL_CreateWindow(String title, int x, int y, int w, int h, int flags)
    native "SDL_CreateWindow";
