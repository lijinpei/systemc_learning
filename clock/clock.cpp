#include <systemc>

SC_MODULE(CLOCK) {
  sc_core::sc_port<sc_core::sc_signal_in_if<bool>> clk;
  SC_CTOR(CLOCK) {
    SC_THREAD(thread);
    sensitive << clk;
    dont_initialize();
  }
  void thread() {
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ", value = " << clk->read()
                << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  sc_core::sc_clock clk("clk", 10, sc_core::SC_SEC, 0.2, 10, sc_core::SC_SEC,
                        false);
  CLOCK clock("clock");
  clock.clk(clk);
  sc_core::sc_start(31, sc_core::SC_SEC);
  return 0;
}
