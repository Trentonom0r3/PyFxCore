#pragma once
//define python minimum version as 3.6

#ifdef PYFXLIB_EXPORTS
#define PYFXAPI __declspec(dllexport)
#else
#define PYFXAPI __declspec(dllimport)
#endif


#include <Python.h>
#define Py_LIMITED_API 0x03060000
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

namespace pyfx {

	PYFXAPI std::atomic<bool> isRunning;

	PYFXAPI void InitializePython();

	PYFXAPI void FinalizePython();

} // namespace pyfx

