class SDL_CommonEvent {
  int type;
  int timestamp;

  void fromJsonBase(Map<String, dynamic> map) {
    type = map['type'];
    timestamp = map['timestamp'];
  }
}

class SDL_QuitEvent extends SDL_CommonEvent {
  SDL_QuitEvent.fromJson(Map<String, dynamic> map) {
    fromJsonBase(map);
  }
}

class SDL_WindowEvent extends SDL_CommonEvent{
  int event;
  int data1;
  int data2;

  SDL_WindowEvent.fromJson(Map<String, dynamic> map) {
    fromJsonBase(map);

    event = map['event'];
    data1 = map['data1'];
    data2 = map['data2'];
  }
}

class SDL_MouseMotionEvent extends SDL_CommonEvent{
  int x;
  int xrel;
  int y;
  int yrel;
  int state;
  int which;

  SDL_MouseMotionEvent.fromJson(Map<String, dynamic> map) {
    fromJsonBase(map);

    x = map['x'];
    xrel = map['xrel'];
    y = map['y'];
    yrel = map['yrel'];
    state = map['state'];
    which = map['which'];
  }
}