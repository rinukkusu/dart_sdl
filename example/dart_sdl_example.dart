// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import '../lib/dart_sdl.dart';
import 'dart:async';

main() {
  var initialized = SDL_Init(SDL_INIT_VIDEO);
  print('initialized: ${initialized}');

  var window = SDL_CreateWindow("Test", 0, 0, 100, 100, SDL_WINDOW_OPENGL);
  print('windowCreated: ${window}');

  SDL_SetRenderDrawColor(window, 100, 0, 100, 100);
  SDL_RenderClear(window);
  SDL_RenderPresent(window);

  new Future.delayed(new Duration(seconds: 3));
}
