// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import 'dart-ext:sdl_extension';

num SDL_INIT_VIDEO = 32;
num SDL_WINDOW_OPENGL = 2;

bool SDL_Init(int flags) native "SDL_Init";
int SDL_CreateWindow(String title, int x, int y, int w, int h, int flags)
    native "SDL_CreateWindow";
bool SDL_SetRenderDrawColor(int window, int r, int g, int b, int a)
    native "SDL_SetRenderDrawColor";
bool SDL_RenderClear(int window) native "SDL_RenderClear";
void SDL_RenderPresent(int window) native "SDL_RenderPresent";
