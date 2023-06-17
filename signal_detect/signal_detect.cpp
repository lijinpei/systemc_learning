#include <systemc>

SC_MODULE(SIGNAL_EVENT) {
  sc_core::sc_signal<int> s1, s2;
  SC_CTOR(SIGNAL_EVENT) {
    SC_THREAD(producer1);
    SC_THREAD(producer2);
    SC_THREAD(consumer);

    sensitive << s1 << s2;
    dont_initialize();
  }

  void producer1() {
    int v = 1;
    while (true) {
      s1.write(v++);
      wait(2, sc_core::SC_SEC);
    }
  }
  void producer2() {
    int v = 1;
    while (true) {
      s2 = v++;
      wait(3, sc_core::SC_SEC);
    }
  }
  void consumer() {
    while (true) {
      bool s1_fired = s1.event();
      bool s2_fired = s2.event();
      if (s1_fired && s2_fired) {
        std::cout << sc_core::sc_time_stamp() << ": s1 & s2 triggered"
                  << std::endl;
      } else if (s1_fired) {
        std::cout << sc_core::sc_time_stamp() << ": s1 triggered" << std::endl;
      } else {
        assert(s2_fired);
        std::cout << sc_core::sc_time_stamp() << ": s2 triggered" << std::endl;
      }
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  SIGNAL_EVENT signal_event("signal_event");
  sc_core::sc_start(7, sc_core::SC_SEC);
  return 0;
}
