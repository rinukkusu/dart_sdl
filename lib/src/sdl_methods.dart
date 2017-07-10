// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import 'dart:convert';
import 'dart:math';
import 'sdl_constants.dart';
import 'sdl_events.dart';
import 'sdl_native.dart' as sdl;
import 'sdl_native_objects.dart';
import 'sdl_objects.dart';

int GetCurrentThreadId() => sdl.GetCurrentThreadId();

bool SDL_Init(int flags) => sdl.SDL_Init(flags);

SDL_Window SDL_CreateWindow(String title, Rectangle rect, int flags) {
  var pointer = sdl.SDL_CreateWindow(
      title, rect.left, rect.top, rect.width, rect.height, flags);
  return new SDL_Window_Native(pointer);
}

bool SDL_SetRenderDrawColor(SDL_Window window, SDL_Color color) =>
    sdl.SDL_SetRenderDrawColor(window.data, color.r, color.g, color.b, color.a);

bool SDL_RenderClear(SDL_Window window) => sdl.SDL_RenderClear(window.data);

void SDL_RenderPresent(SDL_Window window) => sdl.SDL_RenderPresent(window.data);

SDL_CommonEvent SDL_PollEvent(SDL_Window window) {
  var event = sdl.SDL_PollEvent(window.data);
  if (event == null) return null;

  var map = JSON.decode(event);

  switch (map['type']) {
    case SDL_QUIT:
      return new SDL_QuitEvent.fromJson(map);
    case SDL_WINDOWEVENT:
      return new SDL_WindowEvent.fromJson(map);
    case SDL_MOUSEMOTION:
      return new SDL_MouseMotionEvent.fromJson(map);

    default:
      return new SDL_CommonEvent()..fromJsonBase(map);
  }
}

void SDL_Delay(int ms) => sdl.SDL_Delay(ms);

void SDL_SetWindowTitle(SDL_Window window, String title) =>
    sdl.SDL_SetWindowTitle(window.data, title);

bool SDL_RenderDrawPoint(SDL_Window window, Point point) =>
    sdl.SDL_RenderDrawPoint(window.data, point.x, point.y);

bool SDL_RenderDrawLine(SDL_Window window, Point p1, Point p2) =>
    sdl.SDL_RenderDrawLine(window.data, p1.x, p1.y, p2.x, p2.y);

bool SDL_ShowCursor(int toggle) => sdl.SDL_ShowCursor(toggle);
