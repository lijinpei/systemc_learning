#include <systemc>

SC_MODULE(COMBINED) {
  sc_core::sc_event e1, e2, e3, e4, e5, e6, e7, e8, e9, e10;
  SC_CTOR(COMBINED) {
    SC_THREAD(trigger);
    SC_THREAD(catcher_0);
    SC_THREAD(catcher_1);
    SC_THREAD(catcher_2and3);
    SC_THREAD(catcher_4or5);
    SC_THREAD(catcher_timeout_or_6);
    SC_THREAD(catcher_timeout_or_7or8);
    SC_THREAD(catcher_timeout_or_9and10);
  }

  void trigger() {
    e1.notify(1, sc_core::SC_SEC);
    e2.notify(2, sc_core::SC_SEC);
    e3.notify(3, sc_core::SC_SEC);
    e4.notify(4, sc_core::SC_SEC);
    e5.notify(5, sc_core::SC_SEC);
    e6.notify(6, sc_core::SC_SEC);
    e7.notify(7, sc_core::SC_SEC);
    e8.notify(8, sc_core::SC_SEC);
    e9.notify(9, sc_core::SC_SEC);
    e10.notify(10, sc_core::SC_SEC);
  }
  void catcher_0() {
    wait(2, sc_core::SC_SEC);
    std::cout << sc_core::sc_time_stamp() << ": 2sec timeout" << std::endl;
  }
  void catcher_1() {
    wait(e1);
    std::cout << sc_core::sc_time_stamp() << ": catch e1" << std::endl;
  }
  void catcher_2() {
    wait(e1);
    std::cout << sc_core::sc_time_stamp() << ": catcher e1" << std::endl;
  }
  void catcher_2and3() {
    wait(e2 & e3);
    std::cout << sc_core::sc_time_stamp() << ": catch e2 and e3" << std::endl;
  }
  void catcher_4or5() {
    wait(e4 | e5);
    std::cout << sc_core::sc_time_stamp() << ": catch e4 or e5" << std::endl;
  }
  void catcher_timeout_or_6(void) {
    wait(sc_core::sc_time(5, sc_core::SC_SEC), e6);
    std::cout << sc_core::sc_time_stamp() << ": 5sec timeout or catch e6"
              << std::endl;
  }
  void catcher_timeout_or_7or8() {
    wait(sc_core::sc_time(20, sc_core::SC_SEC), e7 | e8);
    std::cout << sc_core::sc_time_stamp()
              << ": 20 sec timeout or catch e7 or e8" << std::endl;
  }
  void catcher_timeout_or_9and10() {
    wait(sc_core::sc_time(20, sc_core::SC_SEC), e9 & e10);
    std::cout << sc_core::sc_time_stamp()
              << ": 20 sec timeout or catch (e9 and e10)" << std::endl;
  }
};

int sc_main(int argc, char* argv[]) {
  COMBINED combined("combined");
  sc_core::sc_start();
  return 0;
}
