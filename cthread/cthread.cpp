#include "systemc"

SC_MODULE(MODULE) {
  sc_core::sc_in<bool> clk;
  SC_CTOR(MODULE) {
    SC_CTHREAD(cthread1, clk);
    SC_CTHREAD(cthread2, clk.pos());
    SC_CTHREAD(cthread3, clk.neg());
  }
  void cthread1() {
    while (true) {
      wait();
      std::cout << sc_core::sc_time_stamp()
                << ", cthread1, value = " << clk->read() << std::endl;
    }
  }
  void cthread2() {
    while (true) {
      wait();
      std::cout << sc_core::sc_time_stamp()
                << ", cthread2, value = " << clk->read() << std::endl;
    }
  }
  void cthread3() {
    while (true) {
      wait();
      std::cout << sc_core::sc_time_stamp()
                << ", cthread3, value = " << clk->read() << std::endl;
    }
  }
};

int sc_main(int argc, char* argv[]) {
  sc_core::sc_clock clk("clk", 10, sc_core::SC_SEC, 0.2, 10, sc_core::SC_SEC,
                        false);
  MODULE mod("module");
  mod.clk(clk);
  sc_core::sc_start(31, sc_core::SC_SEC);
  return 0;
}
