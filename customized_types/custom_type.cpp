#include <iostream>

#include "systemc"

struct CUSTOMIZED_TYPE {
  int x, y;
  CUSTOMIZED_TYPE(int x = 0, int y = 0) : x(x), y(y) {}
  CUSTOMIZED_TYPE& operator=(const CUSTOMIZED_TYPE& other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  bool operator==(const CUSTOMIZED_TYPE& rhs) {
    return x == rhs.x && y == rhs.y;
  }
};

std::ostream& operator<<(std::ostream& os, const CUSTOMIZED_TYPE& val) {
  os << "x = " << val.x << "; y = " << val.y << std::endl;
  return os;
}

inline void sc_trace(sc_core::sc_trace_file* f, const CUSTOMIZED_TYPE& val,
                     const std::string& name) {
  sc_trace(f, val.x, name + ".x");
  sc_trace(f, val.y, name + ".y");
}

SC_MODULE(MODULE) {
  sc_core::sc_signal<CUSTOMIZED_TYPE> s;
  SC_CTOR(MODULE) {
    SC_THREAD(writer);
    SC_THREAD(reader);
    sensitive << s;
    dont_initialize();
  }
  void writer() {
    int x = 1;
    int y = 2;
    while (true) {
      s.write(CUSTOMIZED_TYPE(x++, y++));
      wait(1, sc_core::SC_SEC);
    }
  }
  void reader() {
    while (true) {
      std::cout << sc_core::sc_time_stamp() << " ; receives " << s.read()
                << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  MODULE mod("module");
  sc_core::sc_trace_file* file = sc_core::sc_create_vcd_trace_file("trace");
  sc_core::sc_trace(file, mod.s, "custom_type");
  sc_core::sc_start(2, sc_core::SC_SEC);
  sc_core::sc_close_vcd_trace_file(file);
  return 0;
}
