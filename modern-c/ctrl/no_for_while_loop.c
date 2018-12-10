/**
 * C 不用 for 或 while 循环实现数组的遍历
 * by 代码会说话
 */
int sum(int nums[]) {
  const int count = sizeof(nums) / sizeof(int);
  int sum = 0;
  int i = 0;
add:
  if (i < count) {
    sum += nums[i];
  }
  i++;
  if (i < count) {
    goto add;
  }
  return sum;
}
int main() {
  int nums[] = {3, 4, 5};
  return sum(nums);
}
