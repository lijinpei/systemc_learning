#include <systemc>

SC_MODULE(MULTI) {
  sc_core::sc_signal<int> s1;
  sc_core::sc_signal<int, sc_core::SC_MANY_WRITERS> s2;
  SC_CTOR(MULTI) {
    SC_THREAD(writer1);
    SC_THREAD(writer2);
    SC_THREAD(consumer1);
    sensitive << s1;
    dont_initialize();
    SC_THREAD(consumer2);
    sensitive << s1 << s2;
    dont_initialize();
  }
  void writer1() {
    int v = 1;
    while (true) {
      s1.write(v);
      s2.write(v);
      std::cout << sc_core::sc_time_stamp() << ": writer1 writes " << v++
                << std::endl;
      wait(1, sc_core::SC_SEC);
    }
  }

  void writer2() {
    int v = -1;
    while (true) {
      wait(sc_core::SC_ZERO_TIME);
      s2.write(v);
      std::cout << sc_core::sc_time_stamp() << ": writer2 writes" << v--
                << std::endl;
      wait(1, sc_core::SC_SEC);
    }
  }
  void consumer1() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << ": consumer1 reads s1=" << s1.read() << "; s2=" << s2.read()
                << std::endl;
      wait();
    }
  }
  void consumer2() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << ": consumer2 reads s1=" << s1.read() << "; s2=" << s2.read()
                << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  MULTI consumers("consumers");
  sc_core::sc_start(2, sc_core::SC_SEC);
  return 0;
}
