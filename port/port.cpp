#include <systemc>

SC_MODULE(MODULE1) {
  sc_core::sc_signal<int> s;
  sc_core::sc_port<sc_core::sc_signal_out_if<int>> p;
  SC_CTOR(MODULE1) {
    SC_THREAD(self_write);
    SC_THREAD(self_read);

    sensitive << s;
    dont_initialize();
    SC_THREAD(outside_write);
  }

  void self_write() {
    int val = 1;
    while (true) {
      s.write(val++);
      wait(1, sc_core::SC_SEC);
    }
  }

  void self_read() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << ": reads from own channel, val=" << s.read() << std::endl;
      wait();
    }
  }

  void outside_write() {
    int val = 1;
    while (true) {
      p->write(val++);
      wait(1, sc_core::SC_SEC);
    }
  }
};

SC_MODULE(MODULE2) {
  sc_core::sc_port<sc_core::sc_signal_in_if<int>> p;
  SC_CTOR(MODULE2) {
    SC_THREAD(outside_read);
    sensitive << p;
    dont_initialize();
  }
  void outside_read() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << ": reads from outside channel, val=" << p->read()
                << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  MODULE1 module1("module1");
  MODULE2 module2("module2");

  sc_core::sc_signal<int> s;
  module1.p(s);
  module2.p(s);
  sc_core::sc_start(2, sc_core::SC_SEC);
  return 0;
}
