long absdiff(long x, long y) {
  long res;
  if (x < y) {
    res = y - x;
  } else {
    res = x - y;
  }
  return res;
}