#include <systemc>

SC_MODULE(FIFO) {
  sc_core::sc_fifo<int> f1, f2, f3;
  SC_CTOR(FIFO) : f1(2), f2(2), f3(2) {
    SC_THREAD(generator1);
    SC_THREAD(consumer1);
    SC_THREAD(generator2);
    SC_THREAD(consumer2);
    SC_THREAD(generator3);
    SC_THREAD(consumer3);
  }

  void dump_space(const sc_core::sc_fifo<int>& f) {
    std::cout << "#free/#available=" << f.num_free() << "/"
              << f.num_available();
  }

  void generator_impl(int id, sc_core::sc_fifo<int>& f) {
    int v = 0;
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ":generator" << id << " before write, ";
      dump_space(f);
      std::cout << std::endl;
      f.write(v);
      std::cout << sc_core::sc_time_stamp() << ": generator" << id << " writes "
                << v++ << std::endl;
      std::cout << sc_core::sc_time_stamp() << ":generator" << id << " after write, ";
      dump_space(f);
      std::cout << std::endl;
      wait(1, sc_core::SC_SEC);
    }
  }

  void consumer_impl(int id, sc_core::sc_fifo<int>& f) {
    int v;
    while (true) {
      std::cout << sc_core::sc_time_stamp() << ":consumer" << id << " before read, ";
      dump_space(f);
      std::cout << std::endl;
      f.read(v);
      std::cout << sc_core::sc_time_stamp() << ": consumer" << id << " reads "
                << v << std::endl;
      std::cout << sc_core::sc_time_stamp() << ":consumer" << id << " after read, ";
      dump_space(f);
      std::cout << std::endl;
      wait(3, sc_core::SC_SEC);
    }
  }

  void generator1() { generator_impl(1, f1); }
  void generator2() { generator_impl(2, f2); }
  void generator3() { generator_impl(3, f3); }
  void consumer1() { consumer_impl(1, f1); }
  void consumer2() { consumer_impl(2, f2); }
  void consumer3() { consumer_impl(3, f3); }
};

int sc_main(int argc, char* argv[]) {
  FIFO fifo("fifo");
  sc_core::sc_start(10, sc_core::SC_SEC);
  return 0;
}
