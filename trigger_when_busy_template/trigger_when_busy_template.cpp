#include <deque>
#include <systemc>

SC_MODULE(BufferTrigger_t) {
  sc_core::sc_event trigger, dispatchTask;
  std::deque<bool> bufferedEvent;
  SC_CTOR(BufferTrigger_t) {
    SC_THREAD(trigger_handler);
    sensitive << trigger;
    dont_initialize();
    SC_THREAD(task_procesor);
    sensitive << dispatchTask;
    dont_initialize();
  }
  void trigger_handler() {
    while (true) {
      bufferedEvent.push_back(true);
      dispatchTask.notify();
      wait();
    }
  }
  virtual void process_trigger() = 0;
  void task_procesor() {
    while (true) {
      while (!bufferedEvent.empty()) {
        bufferedEvent.pop_front();
        process_trigger();
      }
      wait();
    }
  }
};

struct MODULE2 : BufferTrigger_t {
  SC_HAS_PROCESS(MODULE2);
  MODULE2(sc_core::sc_module_name name) : BufferTrigger_t(name) {
    SC_THREAD(task_trigger);
  }
  void process_trigger() {
    std::cout << "Process task at " << sc_core::sc_time_stamp() << std::endl;
    wait(1.3, sc_core::SC_SEC);
  }
  void task_trigger() {
    while (sc_core::sc_time_stamp() < sc_core::sc_time(5, sc_core::SC_SEC)) {
      trigger.notify();
      std::cout << "Trigger task at " << sc_core::sc_time_stamp().to_seconds()
                << std::endl;
      wait(1, sc_core::SC_SEC);
    }
  }
};

int sc_main(int argc, char* argv[]) {
  MODULE2 mod2("module2");
  sc_core::sc_start();
  return 0;
}
