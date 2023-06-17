#include <systemc>

SC_MODULE(CONCURRENCY){SC_CTOR(CONCURRENCY){SC_THREAD(thread1);
SC_THREAD(thread2);
}

void thread1() {
  while (true) {
    std::cout << sc_core::sc_time_stamp() << ": thread1" << std::endl;
    wait(2, sc_core::SC_SEC);
  }
}

void thread2() {
  while (true) {
    std::cout << '\t' << sc_core::sc_time_stamp() << ": thread2" << std::endl;
    wait(3, sc_core::SC_SEC);
  }
}
}
;

int sc_main(int argc, char* argv[]) {
  CONCURRENCY concur("concur");
  sc_core::sc_start(10, sc_core::SC_SEC);
  return 0;
}
