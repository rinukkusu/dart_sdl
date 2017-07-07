// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import '../lib/dart_sdl.dart';
import 'dart:async';
import 'dart:math';

main() {
  var initialized = SDL_Init(SDL_INIT_VIDEO);
  print('initialized: ${initialized}');

  var window = SDL_CreateWindow("Test", 30, 30, 600, 400, 0);
  print('windowCreated: ${window}');

  var threadId = GetCurrentThreadId();
  print('current thread: ${threadId}');
  
  Random rand = new Random();
  int fpsCount = 0;
  int eventCount = 0;
  var lastFpsCheck = new DateTime.now();

  while(true) {
    var currentThreadId = GetCurrentThreadId();
    if (currentThreadId != threadId)
      print("THREAD CHANGED!!! $threadId -> $currentThreadId");

    var event;
    while ((event = SDL_PollEvent(window)) != null) {
      print('${new DateTime.now()}: $event');
      eventCount++;
    }

    SDL_SetRenderDrawColor(window, rand.nextInt(255), rand.nextInt(255), rand.nextInt(255), 255);
    SDL_RenderClear(window);
    SDL_RenderPresent(window);

    SDL_Delay(16);

    fpsCount++;
    var now = new DateTime.now();
    if (now.difference(lastFpsCheck).inMilliseconds > 1000) {
      SDL_SetWindowTitle(window, "$fpsCount fps | $eventCount events");
      fpsCount = 0;
      lastFpsCheck = now;
      eventCount = 0;
    }
  }
}
