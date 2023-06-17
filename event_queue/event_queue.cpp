#include <systemc>

SC_MODULE(QUEUE) {
  sc_core::sc_event e;
  sc_core::sc_event_queue eq;
  SC_CTOR(QUEUE) {
    SC_THREAD(trigger);
    SC_THREAD(catch_e);
    sensitive << e;
    dont_initialize();
    SC_THREAD(catch_eq);
    sensitive << eq;
    dont_initialize();
  }

  void trigger() {
    while (true) {
      e.notify(2, sc_core::SC_SEC);
      e.notify(1, sc_core::SC_SEC);
      eq.notify(2, sc_core::SC_SEC);
      eq.notify(1, sc_core::SC_SEC);
      wait(10, sc_core::SC_SEC);
    }
  }
  void catch_e() {
    while (true) {
      std::cout << "sc_time_stamp: " << sc_core::sc_time_stamp()
                << ": catches e" << std::endl;
      wait();
    }
  }
  void catch_eq() {
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ": catches eq" << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  QUEUE queue("queue");
  sc_core::sc_start(20, sc_core::SC_SEC);
  return 0;
}
