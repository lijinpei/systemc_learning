#include <systemc>

SC_MODULE(EVENT) {
  sc_core::sc_event e;
  SC_CTOR(EVENT) {
    SC_THREAD(trigger);
    SC_THREAD(catcher);
  }
  void trigger() {
    while (true) {
      e.notify(1, sc_core::SC_SEC);
      if (sc_core::sc_time_stamp() == sc_core::sc_time(4, sc_core::SC_SEC)) {
        e.cancel();
      }
      wait(2, sc_core::SC_SEC);
    }
  }

  void catcher() {
    while (true) {
      wait(e);
      std::cout << "Event catched at " << sc_core::sc_time_stamp() << std::endl;
    }
  }
};

int sc_main(int argc, char* argv[]) {
  EVENT event("event");
  sc_core::sc_start(9, sc_core::SC_SEC);
  return 0;
}
