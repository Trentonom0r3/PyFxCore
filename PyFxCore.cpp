// PyFxCore.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "PyFxCore.h"

PYFXAPI void pyfx::InitializePython()
{
	try {
		if (pyfx::isRunning) {
			return; // already running
		}
		std::thread t([]() {
			py::initialize_interpreter(); // initialize python interpreter

			pyfx::isRunning = true; // set running flag

			while (pyfx::isRunning) { // run until flag is set to false
				py::gil_scoped_release release; // release GIL
				std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep for 1 second
			}

			py::finalize_interpreter(); // finalize python interpreter when done
			});
		t.detach(); // detach thread
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown exception" << std::endl;
	}
}

void pyfx::FinalizePython()
{
	pyfx::isRunning = false; // set running flag to false
}

