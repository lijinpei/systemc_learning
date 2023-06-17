#include <systemc>

SC_MODULE(SIGNAL) {
  sc_core::sc_signal<int> s;
  SC_CTOR(SIGNAL) { SC_THREAD(readwrite); }
  void readwrite() {
    s.write(3);
    std::cout << "s = " << s << "; " << s.read() << std::endl;
    wait(sc_core::SC_ZERO_TIME);
    std::cout << "after delta_cycle, s = " << s << std::endl;
    s = 4;
    s = 5;
    int tmp = s;
    std::cout << "s = " << tmp << std::endl;
    wait(sc_core::SC_ZERO_TIME);
    std::cout << "after delta_cycle, s = " << s.read() << std::endl;
  }
};

int sc_main(int argc, char* argv[]) {
  SIGNAL signal("signal");
  signal.s = -1;
  sc_core::sc_start();
  return 0;
}
