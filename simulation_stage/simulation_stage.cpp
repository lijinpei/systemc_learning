#include <systemc>

SC_MODULE(STAGE){SC_CTOR(STAGE){std::cout << sc_core::sc_time_stamp()
                                          << " : Elaboration : constructor"
                                          << std::endl;
SC_THREAD(thread);
}
~STAGE() {
  std::cout << sc_core::sc_time_stamp() << " : Cleanup : destructor"
            << std::endl;
}

void thread() {
  std::cout << sc_core::sc_time_stamp() << ": Execution.initialization"
            << std::endl;
  int i = 0;
  while (true) {
    wait(1, sc_core::SC_SEC);
    std::cout << sc_core::sc_time_stamp() << ": Execution.simulation"
              << std::endl;
    if (++i >= 2) {
      sc_core::sc_stop();
    }
  }
}
void before_end_of_elaboration() override {
  std::cout << "before_end_elaboration" << std::endl;
}
void end_of_elaboration() override {
  std::cout << "end_of_elaboration" << std::endl;
}
void start_of_simulation() override {
  std::cout << "start_of_simulation" << std::endl;
}
void end_of_simulation() override {
  std::cout << "end_of_simulation" << std::endl;
}
}
;

int sc_main(int argc, char* argv[]) {
  STAGE stage("stage");
  sc_core::sc_start();
  return 0;
}
