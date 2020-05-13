#define PY_SSIZE_T_CLEAN
#include "/usr/include/python3.8/Python.h"
#include <iostream>

using namespace std;

static PyObject *pyternals_get_state(PyObject *self, PyObject *args) {
    cout << "Successfully called" << endl;
    return self;
}

static PyMethodDef pyternals_meth[] = {
        {"get_state", pyternals_get_state, METH_VARARGS, "Get the python3.8 interperter internal data"},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pyternals_module = {
        PyModuleDef_HEAD_INIT,
        "pyternals",
        "Get the python3.8 interperter internal data",
        -1,
        pyternals_meth
};

extern "C" PyMODINIT_FUNC PyInit_pyternals(void) {
    return PyModule_Create(&pyternals_module);
}

int main() {
    return 0;
}
