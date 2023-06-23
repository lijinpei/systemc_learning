#include <vector>

#include "systemc"

SC_MODULE(WRITER) {
  sc_core::sc_port<sc_core::sc_signal_out_if<int>> p1;
  sc_core::sc_port<sc_core::sc_signal_out_if<int>, 0> p2;
  sc_core::sc_port<sc_core::sc_signal_out_if<int>, 3> p3;
  sc_core::sc_port<sc_core::sc_signal_out_if<int>, 0,
                   sc_core::SC_ZERO_OR_MORE_BOUND>
      pp4;
  sc_core::sc_port<sc_core::sc_signal_out_if<int>, 1,
                   sc_core::SC_ZERO_OR_MORE_BOUND>
      p5;
  sc_core::sc_port<sc_core::sc_signal_out_if<int>, 3,
                   sc_core::SC_ZERO_OR_MORE_BOUND>
      p6;
  sc_core::sc_port<sc_core::sc_signal_out_if<int>, 3, sc_core::SC_ALL_BOUND> p7;
  std::vector<sc_core::sc_port<sc_core::sc_signal_out_if<int>>> p9;
  SC_CTOR(WRITER) : p9(3) { SC_THREAD(writer); }
  void writer() {
    int v = 1;
    while (true) {
      p9[0]->write(v);
      p7[1]->write(v++);
      wait(1, sc_core::SC_SEC);
    }
  }
};

SC_MODULE(READER) {
  sc_core::sc_port<sc_core::sc_signal_in_if<int>> p1;
  sc_core::sc_port<sc_core::sc_signal_in_if<int>, 0> p2;
  sc_core::sc_port<sc_core::sc_signal_in_if<int>, 3> p3;
  sc_core::sc_port<sc_core::sc_signal_in_if<int>, 0,
                   sc_core::SC_ZERO_OR_MORE_BOUND>
      p4;
  sc_core::sc_port<sc_core::sc_signal_in_if<int>, 1,
                   sc_core::SC_ZERO_OR_MORE_BOUND>
      p5;
  sc_core::sc_port<sc_core::sc_signal_in_if<int>, 3,
                   sc_core::SC_ZERO_OR_MORE_BOUND>
      p6;
  sc_core::sc_port<sc_core::sc_signal_in_if<int>, 3, sc_core::SC_ALL_BOUND> p7;
  std::vector<sc_core::sc_port<sc_core::sc_signal_in_if<int>>> p9;
  SC_CTOR(READER) : p9(3) {
    SC_THREAD(reader7);
    sensitive << p7;
    dont_initialize();
    SC_THREAD(reader9);
    sensitive << p9[0] << p9[1] << p9[2];
    dont_initialize();
  }
  void reader7() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << " ; reader7, port 0/1/2 = " << p7[0]->read() << "/"
                << p7[1]->read() << "/" << p7[2]->read() << std::endl;
      wait();
    }
  }
  void reader9() {
    while (true) {
      std::cout << sc_core::sc_time_stamp()
                << " ; reaader9, port 0/1/2 = " << p9[0]->read() << "/"
                << p9[1]->read() << "/" << p9[2]->read() << std::endl;
      wait();
    }
  }
};

int sc_main(int argc, char* argv[]) {
  WRITER writer("writer");
  READER reader("reader");

  sc_core::sc_signal<int> s1;
  std::vector<sc_core::sc_signal<int>> s2(10);
  std::vector<sc_core::sc_signal<int>> s3(3);

  sc_core::sc_signal<int> s5;
  std::vector<sc_core::sc_signal<int>> s6(3);
  std::vector<sc_core::sc_signal<int>> s7(3);

  std::vector<sc_core::sc_signal<int>> s9(3);

  writer.p1(s1);
  reader.p1(s1);
  for (unsigned i = 0; i < s2.size(); ++i) {
    writer.p2(s2[i]);
    reader.p2(s2[i]);
  }
  for (unsigned i = 0; i < s3.size(); ++i) {
    writer.p3(s3[i]);
    reader.p3(s3[i]);
  }
  writer.p5(s5);
  reader.p5(s5);
  for (unsigned i = 0; i < s6.size(); ++i) {
    writer.p6(s6[i]);
    reader.p6(s6[i]);
  }
  for (unsigned i = 0; i < s7.size(); ++i) {
    writer.p7(s7[i]);
    reader.p7(s7[i]);
  }
  for (unsigned i = 0; i < s9.size(); ++i) {
    writer.p9[i](s9[i]);
    reader.p9[i](s9[i]);
  }
  sc_core::sc_start(2, sc_core::SC_SEC);
  return 0;
}
