#include <systemc>

SC_MODULE(PROCESS) {
  sc_core::sc_clock clk;
  SC_CTOR(PROCESS) : clk("clk", 1, sc_core::SC_SEC) {
    SC_METHOD(method);
    SC_THREAD(thread);
    SC_CTHREAD(cthread, clk);
  }

  void method() {
    std::cout << "method triggered @ " << sc_core::sc_time_stamp() << std::endl;
    next_trigger(sc_core::sc_time(1, sc_core::SC_SEC));
  }
  void thread() {
    while (true) {
      std::cout << "thread triggered @ " << sc_core::sc_time_stamp()
                << std::endl;
      wait(1, sc_core::SC_SEC);
    }
  }
  void cthread() {
    while (true) {
      std::cout << "cthread triggered @ " << sc_core::sc_time_stamp()
                << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  PROCESS process("process");
  std::cout << "execution phase begin @ " << sc_core::sc_time_stamp()
            << std::endl;
  sc_start(2, sc_core::SC_SEC);
  std::cout << "execution phase ends @ " << sc_core::sc_time_stamp()
            << std::endl;
  return 0;
}
