#include <systemc>

SC_MODULE(WRITER) {
  sc_core::sc_out<bool> p1, p2;
  SC_CTOR(WRITER) {
    SC_THREAD(writer);
    p1.initialize(true);
  }
  void writer() {
    bool v = true;
    while (true) {
      p1->write(v);
      v = !v;
      wait(1, sc_core::SC_SEC);
    }
  }
};

SC_MODULE(READER) {
  sc_core::sc_in<bool> p1, p2;
  SC_CTOR(READER) {
    SC_THREAD(reader1);
    sensitive << p1 << p2;
    dont_initialize();

    SC_THREAD(reader2);
    sensitive << p1.value_changed();
    dont_initialize();

    SC_THREAD(reader3);
    sensitive << p1.neg();
    dont_initialize();

    SC_THREAD(reader4);
    sensitive << p1.pos();
    dont_initialize();
  }
  void reader1() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << " : default_event. p1 = " << p1->read() << "; p2 triggered? "
                << p1->event() << "; p2 triggered? " << p2->event()
                << std::endl;
      wait();
    }
  }
  void reader2() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << " : value_changed_event. p1 = " << p1->read() << std::endl;
      wait();
    }
  }
  void reader3() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << " : negedge_event. p1 = " << p1->read()
                << "; negedge = " << p1->negedge() << std::endl;
      wait();
    }
  }
  void reader4() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << " : posedge_event. p1 = " << p1->read()
                << "; posedge = " << p1->posedge() << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  WRITER writer("writer");
  READER reader("reader");
  sc_core::sc_signal<bool> b1, b2;

  writer.p1(b1);
  writer.p2(b2);
  reader.p1(b1);
  reader.p2(b2);
  sc_start(4, sc_core::SC_SEC);
  return 0;
}
