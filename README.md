# PyFxCore
Dll that aims to serve as a standardized python entry point for After Effects Applications, enabling proper interaction with AME.

# Dependencies
- Pybind11 [x64-windows-static]
- Python 3.6 minimum. I've linked to python 3.12, but you can link to whatever version, just change the VS files!

# Usage (Assuming a general knowledge of c++)
1) Link to `PyFxCore.lib`. (From the proper directory, debug/release).
2) Place  `PyFxCore.dll` in `C:\Program Files\Adobe\Adobe After Effects 202X\Support Files`.
3) In your plugin code, use `py::gil_scoped_acquire acquire;`, and then perform whatever python stuff you'd like.
4) That's it! Simple as that! `PyFxCore.dll` will take care of python cleanup for you!
