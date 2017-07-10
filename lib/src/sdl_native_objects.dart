import 'dart:convert';
import 'sdl_objects.dart';

class SDL_Window_Native implements SDL_Window {
  num data;

  SDL_Window_Native(this.data);
}

class SDL_Surface_Native implements SDL_Surface {
  num data;

  SDL_Surface_Native(this.data);
}

class SDL_Texture_Native implements SDL_Texture {
  num data;
  int width;
  int height;

  SDL_Texture_Native(String json) {
    Map map = JSON.decode(json);
    data = num.parse(map['data']);
    width = map['width'];
    height = map['height'];
  }
}

class TTF_Font_Native implements TTF_Font {
  num data;

  TTF_Font_Native(this.data);
}