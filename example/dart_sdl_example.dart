// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import '../lib/dart_sdl.dart';

main() {
  var awesome = SDL_Init(SDL_INIT_VIDEO);
  print('awesome: ${awesome}');
}
