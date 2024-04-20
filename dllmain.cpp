#include "pch.h"
#include <Python.h>
#define Py_LIMITED_API 0x03060000
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <atomic>
#include <thread>
#include <iostream>

namespace py = pybind11;
static std::atomic<bool> isRunning(false);
std::thread interpreterThread; // Keep track of the thread

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!isRunning.exchange(true)) { // Atomically set the running flag and check previous value
            interpreterThread = std::thread([]() {
                py::initialize_interpreter(); // Initialize Python interpreter

                while (isRunning.load()) { // Run until flag is set to false
                    py::gil_scoped_release release; // Release GIL
                    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
                }

                py::finalize_interpreter(); // Finalize Python interpreter when done
                });
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        // Optional: Code for handling thread attach/detach
        break;
    case DLL_PROCESS_DETACH:
        isRunning = false; // Set running flag to false to initiate cleanup
        if (interpreterThread.joinable()) {
            interpreterThread.join(); // Ensure the thread completes before unloading DLL
        }
        break;
    }
    return TRUE;
}
