#include <deque>

#include "systemc"

SC_MODULE(MODULE) {
  sc_core::sc_event trigger, dispatchTask;
  std::deque<bool> bufferedEvent;
  SC_CTOR(MODULE) {
    SC_THREAD(task_trigger);
    SC_THREAD(trigger_handler);
    sensitive << trigger;
    dont_initialize();
    SC_THREAD(task_processor);
    sensitive << dispatchTask;
    dont_initialize();
  }
  void task_trigger() {
    while (sc_core::sc_time_stamp() < sc_core::sc_time(5, sc_core::SC_SEC)) {
      trigger.notify();
      std::cout << "Trigger task at " << sc_core::sc_time_stamp().to_seconds()
                << std::endl;
      wait(1, sc_core::SC_SEC);
    }
  }
  void trigger_handler() {
    while (true) {
      bufferedEvent.push_back(true);
      dispatchTask.notify();
      wait();
    }
  }
  void task_processor() {
    while (true) {
      while (!bufferedEvent.empty()) {
        bufferedEvent.pop_front();
        std::cout << "Process task at " << sc_core::sc_time_stamp()
                  << std::endl;
        wait(1.3, sc_core::SC_SEC);
      }
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  MODULE mod("module");
  sc_core::sc_start();
  return 0;
}
