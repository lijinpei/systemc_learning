#include "systemc"

SC_MODULE(MODULE) {
  sc_core::sc_port<sc_core::sc_signal<int>> p;
  SC_CTOR(MODULE) {
    SC_REPORT_WARNING("ctor", "register function");
    SC_THREAD(writer);
    SC_THREAD(reader);
    sensitive << p;
    dont_initialize();
  }
  void writer() {
    int v = 1;
    while (true) {
      SC_REPORT_INFO("writer", ("writer" + std::to_string(v)).c_str());
      p->write(v++);
      wait(1, sc_core::SC_SEC);
    }
  }
  void reader() {
    while (true) {
      SC_REPORT_INFO("reader", ("reader" + std::to_string(p->read())).c_str());
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  sc_core::sc_report_handler::set_log_file_name("report.log");
  sc_core::sc_report_handler::set_actions("writer", sc_core::SC_INFO,
                                          sc_core::SC_LOG);
  MODULE mod("module");
  sc_core::sc_signal<int> s;
  mod.p(s);
  SC_REPORT_INFO("main", "simulation start");
  sc_core::sc_start(2, sc_core::SC_SEC);
  SC_REPORT_INFO("main", "simulation ends");
  return 0;
}
