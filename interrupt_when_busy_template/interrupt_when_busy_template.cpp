#include "systemc"

struct sc_event2 : sc_core::sc_event {
  sc_core::sc_time remainingTime, doneTime;
  bool isRuning = false;
  void notify(sc_core::sc_time t) {
    isRuning = true;
    remainingTime = t;
    doneTime = sc_core::sc_time_stamp() + remainingTime;
    sc_event::notify(t);
  }
  void pause() {
    remainingTime = doneTime - sc_core::sc_time_stamp();
    cancel();
  }
  void resume() { notify(remainingTime); }
  void abort() {
    isRuning = false;
    cancel();
  }
  operator bool() { return isRuning; }
};

SC_MODULE(AllowInterrupt_t) {
  sc_core::sc_event task, dispatchTask, interrupt;
  sc_event2 taskDone;
  int option;
  SC_HAS_PROCESS(AllowInterrupt_t);
  AllowInterrupt_t(sc_core::sc_module_name name, int option = 0)
      : sc_module(name), option(option) {
    SC_THREAD(task_handler);
    sensitive << task;
    dont_initialize();
    SC_THREAD(task_processor);
    dont_initialize();
    SC_THREAD(task_done);
    sensitive << taskDone;
    dont_initialize();
    SC_THREAD(interrupt_handler);
    sensitive << interrupt;
    dont_initialize();
  }
  void task_handler() {
    while (true) {
      dispatchTask.notify();
      wait();
    }
  }
  void interrupt_handler() {
    while (true) {
      std::cout << name() << ": Task interrupted at "
                << sc_core::sc_time_stamp() << std::endl;
      if (option == 1 && taskDone) {
        taskDone.pause();
      } else {
        taskDone.abort();
      }
      interrupt_processor();
      if (option == 1 && taskDone) {
        taskDone.resume();
      }
      wait();
    }
  }
  void task_done() {
    while (true) {
      taskDone.isRuning = false;
      std::cout << name() << ": Task complete at " << sc_core::sc_time_stamp()
                << std::endl;
      wait();
    }
  }
  virtual void task_processor() = 0;
  virtual void interrupt_processor() = 0;
};

struct MODULE2 : AllowInterrupt_t {
  SC_HAS_PROCESS(MODULE2);
  MODULE2(sc_core::sc_module_name name, int option)
      : AllowInterrupt_t(name, option) {
    SC_THREAD(task_trigger);
    SC_THREAD(interrupt_trigger);
  }
  void interrupt_processor() { wait(0.3, sc_core::SC_SEC); }
  void task_processor() {
    while (true) {
      std::cout << name() << ": Task start at " << sc_core::sc_time_stamp()
                << std::endl;
      taskDone.notify(sc_core::sc_time(0.5, sc_core::SC_SEC));
      wait();
    }
  }
  void task_trigger() {
    while (sc_core::sc_time_stamp() < sc_core::sc_time(3, sc_core::SC_SEC)) {
      task.notify();
      wait(1, sc_core::SC_SEC);
    }
  }
  void interrupt_trigger() {
    wait(0.2, sc_core::SC_SEC);
    while (sc_core::sc_time_stamp() < sc_core::sc_time(2, sc_core::SC_SEC)) {
      interrupt.notify();
      wait(1, sc_core::SC_SEC);
    }
  }
};

int sc_main(int argc, char* argv[]) {
  MODULE2 mod2a("module2a", 0);
  MODULE2 mod2b("module2b", 1);
  sc_core::sc_start();
  return 0;
}
