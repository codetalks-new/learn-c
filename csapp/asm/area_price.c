
long calc_area(long width, long height) {
  return width * height;
}
long calc_area_price(long width, long height, long unit_price) {
  long area = calc_area(width, height);
  long price = area * unit_price;
  return price;
}
int main() {
  long width = 3;
  long height = 4;
  long unit_price = 5;
  long price = calc_area_price(width, height, 5);
  return (int)price;
}