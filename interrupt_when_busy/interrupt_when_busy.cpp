#include "systemc"

SC_MODULE(MODULE) {
  sc_core::sc_event trigger, dispatchTask, interrupt, taskDone;
  SC_HAS_PROCESS(MODULE);
  int option;
  sc_core::sc_time taskDoneTime = sc_core::SC_ZERO_TIME,
                   taskRemainingTime = sc_core::SC_ZERO_TIME;
  MODULE(sc_core::sc_module_name name, int option = 0)
      : sc_module(name), option(option) {
    SC_THREAD(task_trigger);
    SC_THREAD(interrupt_generator);
    SC_THREAD(trigger_handler);
    sensitive << trigger;
    dont_initialize();
    SC_THREAD(task_processor);
    sensitive << dispatchTask;
    dont_initialize();
    SC_THREAD(interrupt_handler);
    sensitive << interrupt;
    dont_initialize();
    SC_THREAD(task_done);
    sensitive << taskDone;
    dont_initialize();
  }
  void task_trigger() {
    while (sc_core::sc_time_stamp() < sc_core::sc_time(2, sc_core::SC_SEC)) {
      trigger.notify();
      std::cout << name() << ": Trigger task at " << sc_core::sc_time_stamp()
                << std::endl;
      wait(1, sc_core::SC_SEC);
    }
  }
  void interrupt_generator() {
    wait(0.2, sc_core::SC_SEC);
    while (sc_core::sc_time_stamp() < sc_core::sc_time(2, sc_core::SC_SEC)) {
      interrupt.notify();
      std::cout << name() << ": Interrupt task at " << sc_core::sc_time_stamp()
                << std::endl;
      wait(1, sc_core::SC_SEC);
    }
  }
  void trigger_handler() {
    while (true) {
      dispatchTask.notify();
      wait();
    }
  }
  void task_processor() {
    while (true) {
      std::cout << name() << ": Process task at " << sc_core::sc_time_stamp()
                << std::endl;
      taskRemainingTime = sc_core::sc_time(0.5, sc_core::SC_SEC);
      taskDone.notify(taskRemainingTime);
      taskDoneTime = sc_core::sc_time_stamp() + taskRemainingTime;
      wait();
    }
  }
  void interrupt_handler() {
    while (true) {
      taskDone.cancel();
      if (taskRemainingTime > sc_core::SC_ZERO_TIME) {
        if (option == 0) {
          std::cout << name() << ": Process task aborted at "
                    << sc_core::sc_time_stamp() << std::endl;
        } else if (option == 1) {
          taskRemainingTime = (taskDoneTime - sc_core::sc_time_stamp());
          wait(0.3, sc_core::SC_SEC);
          std::cout << name() << ": Process task resumed at "
                    << sc_core::sc_time_stamp() << std::endl;
          taskDone.notify(taskRemainingTime);
          taskDoneTime = sc_core::sc_time_stamp() + taskRemainingTime;
        }
      }
      wait();
    }
  }
  void task_done() {
    while (true) {
      taskRemainingTime = sc_core::SC_ZERO_TIME;
      std::cout << name() << ": Task completes at " << sc_core::sc_time_stamp()
                << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  MODULE mod0("module0");
  MODULE mod1("module1");
  sc_core::sc_start();
  return 0;
}
