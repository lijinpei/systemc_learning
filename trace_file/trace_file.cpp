#include <systemc>

SC_MODULE(MODULE) {
	sc_core::sc_port<sc_core::sc_signal<int>> p;
	SC_CTOR(MODULE) {
		SC_THREAD(writer);
	}
	void writer() {
		int v = 1;
		while (true) {
			p->write(v++);
			wait(1, sc_core::SC_SEC);
		}
	}
};

int sc_main(int argc, char* argv[]) {
	MODULE mod("module");
	sc_core::sc_signal<int> s;
	mod.p(s);
	sc_core::sc_trace_file* file = sc_core::sc_create_vcd_trace_file("trace");
	sc_core::sc_trace(file, s, "signal");
	sc_core::sc_start(5, sc_core::SC_SEC);
	sc_core::sc_close_vcd_trace_file(file);
	return 0;
}
