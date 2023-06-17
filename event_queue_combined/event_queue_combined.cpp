#include <systemc>

SC_MODULE(QUEUE_COMBINED) {
  sc_core::sc_event_queue eq1, eq2;
  SC_CTOR(QUEUE_COMBINED) {
    SC_THREAD(trigger);
    SC_THREAD(catcher);

    sensitive << eq1 << eq2;
    dont_initialize();
  }

  void trigger() {
    eq1.notify(1, sc_core::SC_SEC);
    eq1.notify(2, sc_core::SC_SEC);
    eq2.notify(2, sc_core::SC_SEC);
    eq2.notify(3, sc_core::SC_SEC);
  }

  void catcher() {
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ": catches trigger" << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  QUEUE_COMBINED combined("combined");
  sc_core::sc_start();
  return 0;
}
