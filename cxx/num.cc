#include <iostream>
#include <iomanip>

void print_line(int num) {
  for (int i=0; i<=num; i++)
    std::cout/* << std::setw(2)*/ << i << " ";
  std::cout << std::endl;
}
void print_nums(int num) {
  for (int i=0; i <=num; i++) {
    print_line(i);
  }
}

void usage(const char *prog) {
  std::cout << "usage: " << prog << " number to print" << std::endl;
}

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    usage(argv[0]);
    exit(1);
  }
  print_nums(atol(argv[1]));
  return 0;
}
