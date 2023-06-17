#include <systemc>

SC_MODULE(SIGNAL_BOOL) {
  sc_core::sc_signal<bool> b;
  SC_CTOR(SIGNAL_BOOL) {
    SC_THREAD(writer);

    SC_THREAD(consumer);
    sensitive << b;
    dont_initialize();

    SC_THREAD(consumer_pos);
    sensitive << b.posedge_event();
    dont_initialize();
    SC_THREAD(consumer_neg);
    sensitive << b.negedge_event();
    dont_initialize();
  }
  void writer() {
    bool v = true;
    while (true) {
      b.write(v);
      v = !v;
      wait(1, sc_core::SC_SEC);
    }
  }
  void consumer() {
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ": consumer receives ";
      if (b.posedge()) {
        std::cout << "posedge";
      } else {
        std::cout << "negedge";
      }
      std::cout << ", b = " << b << std::endl;
      wait();
    }
  }
  void consumer_pos() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << ": consumer_pos receives posedge, b = " << b << std::endl;
      wait();
    }
  }
  void consumer_neg() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << ": connsumer_neg receives negedge, b = " << b << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  SIGNAL_BOOL signal_bool("signal_bool");
  sc_core::sc_start(4, sc_core::SC_SEC);
  return 0;
}
