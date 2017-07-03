// Copyright (c) 2017, 'rinukkusu'. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

import 'dart-ext:sdl_extension';

num SDL_INIT_VIDEO = "\u{000020}".runes.first;

bool SDL_Init(int flags) native "SDL_Init";
