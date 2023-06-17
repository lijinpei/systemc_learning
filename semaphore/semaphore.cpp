#include <systemc>

SC_MODULE(SEMAPHORE) {
  sc_core::sc_semaphore s;
  SC_CTOR(SEMAPHORE) : s(2) {
    SC_THREAD(thread_1);
    SC_THREAD(thread_2);
    SC_THREAD(thread_3);
  }
  void thread_1() {
    while (true) {
      if (s.trywait() == -1) {
        s.wait();
      }
      std::cout << sc_core::sc_time_stamp() << ": locked by thread_1, value is "
                << s.get_value() << std::endl;
      wait(1, sc_core::SC_SEC);
      s.post();
      std::cout << sc_core::sc_time_stamp()
                << ": unlocked by thread_1, value is " << s.get_value()
                << std::endl;
      wait(sc_core::SC_ZERO_TIME);
    }
  }

  void thread_2() {
    while (true) {
      if (s.trywait() == -1) {
        s.wait();
      }
      std::cout << sc_core::sc_time_stamp() << ": locked by thread_2, value is "
                << s.get_value() << std::endl;
      wait(1, sc_core::SC_SEC);
      s.post();
      std::cout << sc_core::sc_time_stamp()
                << ": unlocked by thread_2, value is " << s.get_value()
                << std::endl;
      wait(sc_core::SC_ZERO_TIME);
    }
  }
  void thread_3() {
    while (true) {
      if (s.trywait() == -1) {
        s.wait();
      }
      std::cout << sc_core::sc_time_stamp() << ": locked by thread_3, value is "
                << s.get_value() << std::endl;
      wait(1, sc_core::SC_SEC);
      s.post();
      std::cout << sc_core::sc_time_stamp()
                << ": unlocked by thread_3, value is " << s.get_value()
                << std::endl;
      wait(sc_core::SC_ZERO_TIME);
    }
  }
};

int sc_main(int argc, char* argv[]) {
  SEMAPHORE semaphore("semaphore");
  sc_core::sc_start(4, sc_core::SC_SEC);
  return 0;
}
