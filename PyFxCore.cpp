// PyFxCore.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "PyFxCore.h"

PYFXAPI void pyfx::InitializePython()
{
	try {
		std::thread t([]() {
			py::initialize_interpreter();

			pyfx::isRunning = true;
			while (pyfx::isRunning) {
				py::gil_scoped_release release;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			py::finalize_interpreter();
			});
		t.detach();
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
	pyfx::isRunning = false;
}

