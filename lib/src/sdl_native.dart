// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import 'dart-ext:sdl_extension';

int GetCurrentThreadId() native "GetCurrentThreadId";
bool SDL_Init(int flags) native "SDL_Init";
int SDL_CreateWindow(String title, int x, int y, int w, int h, int flags)
    native "SDL_CreateWindow";
bool SDL_SetRenderDrawColor(int windowPtr, int r, int g, int b, int a)
    native "SDL_SetRenderDrawColor";
bool SDL_RenderClear(int windowPtr) native "SDL_RenderClear";
void SDL_RenderPresent(int windowPtr) native "SDL_RenderPresent";
String SDL_PollEvent(int windowPtr) native "SDL_PollEvent";
void SDL_Delay(int ms) native "SDL_Delay";
void SDL_SetWindowTitle(int windowPtr, String title)
    native "SDL_SetWindowTitle";
bool SDL_RenderDrawPoint(int windowPtr, int x, int y)
    native "SDL_RenderDrawPoint";
bool SDL_RenderDrawLine(int windowPtr, int x1, int y1, int x2, int y2)
    native "SDL_RenderDrawLine";
bool SDL_ShowCursor(int toggle) native "SDL_ShowCursor";
String SDL_CreateTextureFromSurface(int windowPtr, int surfacePtr)
    native "SDL_CreateTextureFromSurface";
bool SDL_RenderCopy(int windowPtr, int texturePtr, int sx, int sy, int sw,
    int sh, int dx, int dy, int dw, int dh) native "SDL_RenderCopy";
void SDL_FreeSurface(int surfacePtr) native "SDL_FreeSurface";

// TTF
bool TTF_Init() native "TTF_Init";
int TTF_OpenFont(String filePath, int fontSize) native "TTF_OpenFont";
int TTF_RenderText(int fontPtr, String text, int r, int g, int b, int a)
    native "TTF_RenderText";
int TTF_RenderText_Blended(int fontPtr, String text, int r, int g, int b, int a)
    native "TTF_RenderText_Blended";

// IMG
bool IMG_Init(int flags) native "IMG_Init";