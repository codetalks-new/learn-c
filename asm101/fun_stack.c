
long get_unit_price() {
  return 6;
}

long calc_area(long length, long width) {
  return length * width;
}

long calc_price(long length, long width) {
  long area_size = calc_area(length, width);
  long unit_price = get_unit_price();
  long price = area_size * unit_price;
  return price;
}

int main(int argc, char *argv[]) {
  long length = 4;
  long width = 5;
  return calc_price(length, width);
}
/**
 *

call 7d ff ff ff
call 5d ff ff ff

 7d

 0x100 - 7d
  fa3
   83
  f00
 */