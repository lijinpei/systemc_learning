#include <systemc>

SC_MODULE(DELTA) {
  int x = 1, y = 1;
  SC_CTOR(DELTA) {
    SC_THREAD(add_x);
    SC_THREAD(multiply_x);
    SC_THREAD(add_y);
    SC_THREAD(multiply_y);
  }
  void add_x() {
    std::cout << "add_x: " << x << " + 2"
              << " = ";
    x += 2;
    std::cout << x << std::endl;
  }
  void multiply_x() {
    wait(sc_core::SC_ZERO_TIME);
    std::cout << "multiply_x: " << x << " * 3"
              << " = ";
    x *= 3;
    std::cout << x << std::endl;
  }
  void add_y() {
    wait(sc_core::SC_ZERO_TIME);
    std::cout << "add_y: " << y << " + 2"
              << " = ";
    y += 2;
    std::cout << y << std::endl;
  }
  void multiply_y() {
    std::cout << "multiply_y: " << y << " * 3"
              << " = ";
    y *= 3;
    std::cout << y << std::endl;
  }
};

int sc_main(int argc, char* argv[]) {
  DELTA delta("delta");
  sc_core::sc_start();
  return 0;
}
