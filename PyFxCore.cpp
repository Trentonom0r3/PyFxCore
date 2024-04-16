// PyFxCore.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "PyFxCore.h"

PYFXAPI void pyfx::InitializePython()
{
	try {
		std::thread([]() {
			py::initialize_interpreter();
			py::gil_scoped_release release;
			}).detach();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown exception" << std::endl;
	}
}

PYFXAPI void pyfx::FinalizePython()
{
	try {
		py::finalize_interpreter();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown exception" << std::endl;
	}
}

