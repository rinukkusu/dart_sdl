// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import '../lib/dart_sdl.dart';
import 'dart:math';

List<List<Point>> cursor = [
  [new Point(0, 0), new Point(10, 10)],
  [new Point(10, 10), new Point(0, 15)],
  [new Point(0, 15), new Point(0, 0)],
];

int window;
int threadId;

Random rand = new Random();
int fpsCount = 0;
int eventCount = 0;
var lastFpsCheck = new DateTime.now();

Point mousePos = new Point(0, 0);

main() {
  createWindow();

  SDL_ShowCursor(SDL_DISABLE);

  while(true) {
    checkThread();
    handleEvents();
    calcFps();

    SDL_SetRenderDrawColor(window, 255, 255, 255, 255);
    SDL_RenderClear(window);

    SDL_SetRenderDrawColor(window, rand.nextInt(255), rand.nextInt(255), rand.nextInt(255), 255);
    

    cursor.forEach((p) {
      SDL_RenderDrawLine(window, 
          mousePos.x + p[0].x, mousePos.y + p[0].y,
          mousePos.x + p[1].x, mousePos.y + p[1].y);
    });

    SDL_RenderPresent(window);
    SDL_Delay(1);
  }
}

void createWindow() {
  var initialized = SDL_Init(SDL_INIT_VIDEO);
  print('initialized: ${initialized}');

  window = SDL_CreateWindow("Test", 30, 30, 800, 600, SDL_WINDOW_RESIZABLE);
  print('windowCreated: ${window}');

  threadId = GetCurrentThreadId();
  print('current thread: ${threadId}');
}

void checkThread() {
  var currentThreadId = GetCurrentThreadId();
  if (currentThreadId != threadId) {
    throw "THREAD CHANGED!!! $threadId -> $currentThreadId";
  }
}

void handleEvents() {
  SDL_CommonEvent event;
    while ((event = SDL_PollEvent(window)) != null) {
      print('${new DateTime.now()}: ${event.runtimeType}');
      eventCount++;

      if (event is SDL_QuitEvent) throw 'QUIT! :)';
      if (event is SDL_MouseMotionEvent) { 
        SDL_MouseMotionEvent mouseEvent = event;
        mousePos = new Point(mouseEvent.x,  mouseEvent.y); 
      }
    }
}

void calcFps() {
  fpsCount++;
  var now = new DateTime.now();
  if (now.difference(lastFpsCheck).inMilliseconds > 1000) {
    var fpsString = "$fpsCount fps | $eventCount events";
    SDL_SetWindowTitle(window, fpsString);
    print(fpsString);
    fpsCount = 0;
    lastFpsCheck = now;
    eventCount = 0;
  }
}