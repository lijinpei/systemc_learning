#include <systemc>
#include <vector>

SC_MODULE(RESOLVED_SIGNAL) {
  sc_core::sc_signal_resolved rv;
  std::vector<sc_dt::sc_logic> levels;
  SC_CTOR(RESOLVED_SIGNAL)
      : levels(std::vector<sc_dt::sc_logic>{
            sc_dt::sc_logic_0, sc_dt::sc_logic_1, sc_dt::sc_logic_Z,
            sc_dt::sc_logic_X}) {
    SC_THREAD(writer1);
    SC_THREAD(writer2);
    SC_THREAD(consumer);
  }

  void writer1() {
    int idx = 0;
    while (true) {
      rv.write(levels[idx++ % 4]);
      wait(1, sc_core::SC_SEC);
    }
  }
  void writer2() {
    int idx = 0;
    while (true) {
      rv.write(levels[(idx++ / 4) % 4]);
      wait(1, sc_core::SC_SEC);
    }
  }
  void consumer() {
    wait(1, sc_core::SC_SEC);
    int idx = 0;
    while (true) {
      std::cout << " " << rv.read() << " |";
      if (++idx % 4 == 0) {
        std::cout << std::endl;
      }
      wait(1, sc_core::SC_SEC);
    }
  }
};

int sc_main(int argc, char* argv[]) {
  RESOLVED_SIGNAL resolved("resolved");
  sc_core::sc_start(17, sc_core::SC_SEC);
  return 0;
}
