typedef pair<point, point> halfplane;

point dir(halfplane h) {
  return h.second - h.first;
}
bool belongs(halfplane h, point a) {
  return cross(dir(h), a - h.first) > EPS;
}
bool hpcomp(halfplane ha, halfplane hb) {
  point a = dir(ha), b = dir(hb);
  if (parallel(a, b) && inner(a, b) > EPS)
    return cross(b, ha.first - hb.first) < -EPS;
  if (b.y*a.y > EPS) return cross(a, b) > EPS;
  else if (fabs(b.y) < EPS && b.x > EPS) return false;
  else if (fabs(a.y) < EPS && a.x > EPS) return true;
  else return b.y < a.y;
}
polygon intersect(vector<halfplane> H, double W = INF) {
  H.push_back(halfplane(point(-W,-W),point(W,-W)));
  H.push_back(halfplane(point(W,-W),point(W,W)));
  H.push_back(halfplane(point(W,W),point(-W,W)));
  H.push_back(halfplane(point(-W,W),point(-W,-W)));
  sort(H.begin(), H.end(), hpcomp);
  int i = 0;
  while(parallel(dir(H[0]), dir(H[i]))) i++;
  deque<point> P;
  deque<halfplane> S;
  S.push_back(H[i-1]);
  for(; i < (int)H.size(); i++) {
    while(!P.empty() && !belongs(H[i], P.back()))
      P.pop_back(), S.pop_back();
    point df = dir(S.front()), di = dir(H[i]);
    if (P.empty() && cross(df, di) < EPS)
      return polygon();
    P.push_back(lineIntersectSeg(H[i].first, H[i].second,
      S.back().first, S.back().second));
    S.push_back(H[i]);
  }
  while(!belongs(S.back(), P.front()) ||
    !belongs(S.front(), P.back())) {
    while(!belongs(S.back(), P.front()))
      P.pop_front(), S.pop_front();
    while(!belongs(S.front(), P.back()))
      P.pop_back(), S.pop_back();
  }
  P.push_back(lineIntersectSeg(S.front().first,
    S.front().second, S.back().first, S.back().second));
  return polygon(P.begin(), P.end());
}
