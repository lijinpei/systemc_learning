#include <systemc>

SC_MODULE(SENSITIVITY) {
  sc_core::sc_event e1, e2;
  SC_CTOR(SENSITIVITY) {
    SC_THREAD(trigger_1);
    SC_THREAD(trigger_2);
    SC_THREAD(catch_1or2_dyn);
    SC_THREAD(catch_1or2_static);

    sensitive << e1 << e2;
  }
  void trigger_1() {
    wait(sc_core::SC_ZERO_TIME);
    while (true) {
      e1.notify();
      wait(2, sc_core::SC_SEC);
    }
  }
  void trigger_2() {
    wait(sc_core::SC_ZERO_TIME);
    while (true) {
      e2.notify();
      wait(3, sc_core::SC_SEC);
    }
  }
  void catch_1or2_dyn() {
    wait(sc_core::SC_ZERO_TIME);
    while (true) {
      wait(e1 | e2);
      std::cout << "Dynamic sensitivity: e1 or e2 @ "
                << sc_core::sc_time_stamp() << std::endl;
    }
  }
  void catch_1or2_static() {
    while (true) {
      wait();
      std::cout << "Static sensitivity: e1 or e2 @ " << sc_core::sc_time_stamp()
                << std::endl;
    }
  }
};

int sc_main(int argc, char* argv[]) {
  SENSITIVITY sensitivity("sensitivity");
  sc_core::sc_start(7, sc_core::SC_SEC);
  return 0;
}
