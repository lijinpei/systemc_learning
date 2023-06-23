#include "systemc"

class SIGNAL : public sc_core::sc_channel,
               public sc_core::sc_signal_inout_if<int> {
 public:
  SC_HAS_PROCESS(SIGNAL);
  SIGNAL(sc_core::sc_module_name name = sc_core::sc_gen_unique_name("SIG"))
      : sc_core::sc_channel(name) {}
  void write(const int& v) {
    if (v != m_val) {
      m_val = v;
      e.notify();
    }
  }
  const int& read() const { return m_val; }
  const sc_core::sc_event& value_changed_event() const { return e; }
  const sc_core::sc_event& default_event() const {
    return value_changed_event();
  }
  const int& get_data_ref() const { return m_val; }
  bool event() const { return true; }

 private:
  int m_val = 0;
  sc_core::sc_event e;
};

SC_MODULE(TEST) {
  SIGNAL s;
  SC_CTOR(TEST) {
    SC_THREAD(writer);
    SC_THREAD(reader);
    sensitive << s;
    dont_initialize();
  }
  void writer() {
    int v = 1;
    while (true) {
      s.write(v++);
      wait(1, sc_core::SC_SEC);
    }
  }
  void reader() {
    while (true) {
      std::cout << sc_core::sc_time_stamp() << " : val = " << s.read()
                << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  TEST test("test");
  sc_core::sc_start(2, sc_core::SC_SEC);
  return 0;
}
