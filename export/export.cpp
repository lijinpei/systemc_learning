#include <systemc>

SC_MODULE(MODULE1) {
	sc_core::sc_export<sc_core::sc_signal<int>> p;
	sc_core::sc_signal<int> s;

	SC_CTOR(MODULE1) {
		p(s);
		SC_THREAD(writer);
	}

	void writer() {
		int val = 1;
		while (true) {
			s.write(val++);
			wait(1, sc_core::SC_SEC);
		}
	}
};

SC_MODULE(MODULE2) {
	sc_core::sc_port<sc_core::sc_signal_in_if<int>> p;
	SC_CTOR(MODULE2) {
		SC_THREAD(reader);
		sensitive << p;
		dont_initialize();
	}
	void reader() {
		while (true) {
			std::cout << sc_core::sc_time_stamp() << ": reads from outside channel, val=" << p->read() << std::endl;
			wait();
		}
	}
};

int sc_main(int argc, char* argv[]) {
	MODULE1 module1("module1");
	MODULE2 module2("module2");

	module2.p(module1.p);
	sc_core::sc_start(2, sc_core::SC_SEC);
	return 0;
}
