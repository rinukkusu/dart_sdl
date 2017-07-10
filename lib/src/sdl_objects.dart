class SDL_Color {
  static final RegExp _regCheck = new RegExp(r'[A-Fa-f0-9]{6}');
  final int r, g, b, a;

  const SDL_Color(this.r, this.g, this.b, [this.a = 255]);

  static fromHex(String hexString, [int a = 255]) {
    hexString.replaceFirst('#', '');

    if (!_regCheck.hasMatch(hexString)) {
      throw 'Not a valid HTML color code: \'$hexString\'';
    }

    int r = int.parse('${hexString[0]}${hexString[1]}', radix: 16);
    int g = int.parse('${hexString[2]}${hexString[3]}', radix: 16);
    int b = int.parse('${hexString[4]}${hexString[5]}', radix: 16);

    return new SDL_Color(r, g, b, a);
  }

  static SDL_Color get Black => const SDL_Color(0, 0, 0);
  static SDL_Color get White => const SDL_Color(255, 255, 255);
  static SDL_Color get Gray => const SDL_Color(128, 128, 128);
  static SDL_Color get Red => const SDL_Color(255, 0, 0);
  static SDL_Color get Green => const SDL_Color(0, 255, 0);
  static SDL_Color get Blue => const SDL_Color(0, 0, 255);
}

abstract class SDL_Window {
  final num data;

  SDL_Window(this.data);
}

abstract class SDL_Surface {
  final num data;

  SDL_Surface(this.data);
}

abstract class SDL_Texture {
  final num data;
  final num height;
  final num width;

  SDL_Texture(this.data, this.height, this.width);
}

abstract class TTF_Font {
  final num data;

  TTF_Font(this.data);
}

abstract class SDL_TextureInfo {}