// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import 'dart:convert';
import 'sdl_constants.dart';
import 'sdl_events.dart';
import 'sdl_native.dart' as sdl;

int GetCurrentThreadId() => sdl.GetCurrentThreadId();

bool SDL_Init(int flags) => sdl.SDL_Init(flags);

int SDL_CreateWindow(String title, int x, int y, int w, int h, int flags) => 
    sdl.SDL_CreateWindow(title, x, y, w, h, flags);

bool SDL_SetRenderDrawColor(int window, int r, int g, int b, int a) => 
    sdl.SDL_SetRenderDrawColor(window, r, g, b, a);

bool SDL_RenderClear(int window) => sdl.SDL_RenderClear(window);

void SDL_RenderPresent(int window) => sdl.SDL_RenderPresent(window);

SDL_CommonEvent SDL_PollEvent(int window) {
    var event = sdl.SDL_PollEvent(window);
    if (event == null) return null;

    var map = JSON.decode(event);

    switch(map['type']) {
        case SDL_QUIT: return new SDL_QuitEvent.fromJson(map);
        case SDL_WINDOWEVENT: return new SDL_WindowEvent.fromJson(map);
        case SDL_MOUSEMOTION: return new SDL_MouseMotionEvent.fromJson(map);

        default: return new SDL_CommonEvent()..fromJsonBase(map);
    }
}

void SDL_Delay(int ms) => sdl.SDL_Delay(ms);

void SDL_SetWindowTitle(int window, String title) => sdl.SDL_SetWindowTitle(window, title);

bool SDL_RenderDrawPoint(int window, int x, int y) => sdl.SDL_RenderDrawPoint(window, x, y);

bool SDL_RenderDrawLine(int window, int x1, int y1, int x2, int y2) => sdl.SDL_RenderDrawLine(window, x1, y1, x2, y2);

bool SDL_ShowCursor(int toggle) => sdl.SDL_ShowCursor(toggle);