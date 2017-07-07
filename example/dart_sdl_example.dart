// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import '../lib/dart_sdl.dart';
import 'dart:async';
import 'dart:math';

main() async {
  var initialized = SDL_Init(SDL_INIT_VIDEO);
  print('initialized: ${initialized}');

  var window = SDL_CreateWindow("Test", 30, 30, 100, 100, SDL_WINDOW_OPENGL);
  print('windowCreated: ${window}');
  
  Random rand = new Random();
  
  while(true) {
    var event = SDL_PollEvent(window);
    if (event != null) {
      print('${new DateTime.now()}: $event');
    }

    SDL_SetRenderDrawColor(window, rand.nextInt(255), rand.nextInt(255), rand.nextInt(255), 255);
    SDL_RenderClear(window);
    SDL_RenderPresent(window);

    await new Future.delayed(new Duration(milliseconds: 17));
  }
}
