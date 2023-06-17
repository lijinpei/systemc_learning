#include <systemc>

SC_MODULE(MUTEX) {
  sc_core::sc_mutex m;
  SC_CTOR(MUTEX) {
    SC_THREAD(thread_1);
    SC_THREAD(thread_2);
  }
  void thread_1() {
    while (true) {
      if (m.trylock() == -1) {
        m.lock();
        std::cout << sc_core::sc_time_stamp()
                  << ": thread1 obtained resource by lock()" << std::endl;
      } else {
        std::cout << sc_core::sc_time_stamp()
                  << ": thread_1 obtained resource by trylock()" << std::endl;
      }
      wait(1, sc_core::SC_SEC);
      m.unlock();
      std::cout << sc_core::sc_time_stamp() << ": unlocked by thread_1"
                << std::endl;
      wait(sc_core::SC_ZERO_TIME);
    }
  }
  void thread_2() {
    while (true) {
      if (m.trylock() == -1) {
        m.lock();
        std::cout << sc_core::sc_time_stamp()
                  << ": thread_2 obtained resource by lock()" << std::endl;
      } else {
        std::cout << sc_core::sc_time_stamp()
                  << ": thread_2 obtained resource by trylock()" << std::endl;
      }
      wait(1, sc_core::SC_SEC);
      m.unlock();
      std::cout << sc_core::sc_time_stamp() << ": unlocked by thread_2"
                << std::endl;
      wait(sc_core::SC_ZERO_TIME);
    }
  }
};

int sc_main(int argc, char* argv[]) {
  MUTEX mutex("mutex");
  sc_core::sc_start(4, sc_core::SC_SEC);
  return 0;
}
