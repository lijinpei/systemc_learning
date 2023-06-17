#include <systemc>

SC_MODULE(SUBMODULE1) {
  sc_core::sc_port<sc_core::sc_signal_out_if<int>> p;
  SC_CTOR(SUBMODULE1) { SC_THREAD(writer); }
  void writer() {
    int val = 1;
    while (true) {
      p->write(val++);
      wait(1, sc_core::SC_SEC);
    }
  }
};

SC_MODULE(SUBMODULE2) {
  sc_core::sc_port<sc_core::sc_signal_in_if<int>> p;
  SC_CTOR(SUBMODULE2) {
    SC_THREAD(reader);
    sensitive << p;
    dont_initialize();
  }
  void reader() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << ": reads from channel, val=" << p->read() << std::endl;
      wait();
    }
  }
};

SC_MODULE(MODULE1) {
  sc_core::sc_port<sc_core::sc_signal_out_if<int>> p;
  SUBMODULE1 sub1;
  SC_CTOR(MODULE1) : sub1("sub1") { sub1.p(p); }
};

SC_MODULE(MODULE2) {
  sc_core::sc_port<sc_core::sc_signal_in_if<int>> p;
  SUBMODULE2 sub2;
  SC_CTOR(MODULE2) : sub2("sub2") { sub2.p(p); }
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
