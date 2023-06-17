#include <systemc>

SC_MODULE(PROCESS){SC_CTOR(PROCESS){SC_THREAD(thread);
SC_METHOD(method);
}
void thread() {
  int idx = 0;
  while (true) {
    std::cout << "thread " << idx++ << " @ " << sc_core::sc_time_stamp()
              << std::endl;
    wait(1, sc_core::SC_SEC);
  }
}

void method() {
  int idx = 0;
  std::cout << "method " << idx++ << " @ " << sc_core::sc_time_stamp()
            << std::endl;
  next_trigger(1, sc_core::SC_SEC);
}
}
;

int sc_main(int arvc, char* argv[]) {
  PROCESS process("process");
  sc_core::sc_start(4, sc_core::SC_SEC);
  return 0;
}
