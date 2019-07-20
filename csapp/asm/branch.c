long branch(long a) {
  do {
    a <<= 1;
  } while ((a & a) < 0);
  return a;
}