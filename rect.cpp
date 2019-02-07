struct rect {
  int x1, y1, x2, y2; // x1 < x2, y1 < y2
  rect () {};
  rect (int x1, int y1, int x2, int y2) : x1(x1), x2(x2), y1(y1), y2(y2) {};
  rect inter (rect other) {
    int x3 = max(x1, other.x1);
    int y3 = max(y1, other.y1);
    int x4 = min(x2, other.x2);
    int y4 = min(y2, other.y2);
    return rect(x3, y3, x4, y4);
  }
};
