# PyFxCore
Dll that aims to serve as a standardized python entry point for After Effects Applications, enabling proper interaction with AME.

# Usage (Assuming a general knowledge of c++)
1) Link to `PyFxCore.lib`. (From the proper directory, debug/release)
2) Add `PyFxCore` to your includes.
3) Call `pyfx::InitializePython();`.
  - This Function will handle all initialization for you.
  - When unloading your plugin, call `pyfx::FinalizePython();` to safely finalize python.
4) To call python, simply acquire the GIL using `py::gil_scoped_acquire acquire;` from `Pybind11`.

Because this will be loaded into the AE address space, calling `py::gil_scoped_acquire acquire;` will safely access and wait on threads to be free for use. 
If you have for example-- a central plugin or AEGP that loads `PyFxCore`, you could simply use pure `pybind11` instead of linking to `PyFxCore`. 

I'm looking into how I could possibly initialize with AE itself, so all you would need to do is link to the .lib, and when the .dll gets loaded, it would call the initialization functions. 
