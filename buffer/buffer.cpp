#include <systemc>

SC_MODULE(BUFFER) {
  sc_core::sc_signal<int> s;
  sc_core::sc_buffer<int> b;
  SC_CTOR(BUFFER) {
    SC_THREAD(writer);
    SC_THREAD(consumer1);
    sensitive << s;
    dont_initialize();
    SC_THREAD(consumer2);
    sensitive << b;
    dont_initialize();
  }
  void writer() {
    int val = 1;
    while (true) {
      for (int i = 0; i < 2; ++i) {
        s.write(val);
        b.write(val);
        wait(1, sc_core::SC_SEC);
      }
      val++;
    }
  }
  void consumer1() {
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ": consumer1 receives "
                << s.read() << std::endl;
      wait();
    }
  }
  void consumer2() {
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ": consumer2 receives "
                << b.read() << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  BUFFER buffer("buffer");
  sc_core::sc_start(4, sc_core::SC_SEC);
  return 0;
}
