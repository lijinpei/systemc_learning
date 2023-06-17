#include <systemc>

SC_MODULE(INITIALIZATION) {
  sc_core::sc_event e;
  SC_CTOR(INITIALIZATION) {
    SC_THREAD(trigger);
    SC_THREAD(catcher_1);
    SC_THREAD(catcher_2);
    SC_THREAD(catcher_3);

    sensitive << e;
    dont_initialize();
  }

  void trigger() {
    while (true) {
      e.notify(1, sc_core::SC_SEC);
      wait(2, sc_core::SC_SEC);
    }
  }

  void catcher_1() {
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ": catcher_1 triggered"
                << std::endl;
      wait(e);
    }
  }

  void catcher_2() {
    wait(e);
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ": catcher_2 triggered"
                << std::endl;
      wait(e);
    }
  }

  void catcher_3() {
    wait(e);
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ": catcher_3 triggered"
                << std::endl;
      wait(e);
    }
  }
};

int sc_main(int argc, char* argv[]) {
  INITIALIZATION init("init");
  sc_core::sc_start(4, sc_core::SC_SEC);
  return 0;
}
