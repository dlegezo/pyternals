#define PY_SSIZE_T_CLEAN

#include "/usr/include/python3.8/Python.h"
#include "common.h"
#include <iostream>

using namespace std;

static void print_mem_content(uint8_t *m, int l) {
    for (int i=0; i<l; ++i) {
        cout << hex << (int)m[i] << " ";
    }
    cout << endl;
}

static PyObject *print_basic_info(PyObject *self, PyObject *args) {
    cout << "version: " << Py_GetVersion() << ", ";
    cout << "platform: " << Py_GetPlatform() << ", ";
    cout << "compiler: " << Py_GetCompiler() << ", ";
    cout << "build: " << Py_GetBuildInfo() << "\n";
    return self;
}

static void print_interpreter_state(PyInterpreterState *pis) {
    cout << "--------------------- interpreter state ---------------------" << '\n';
    cout << "interpreter state address: " << hex << pis << ", ";
    cout << "next: " << hex << pis->next << ", ";
    cout << "tstate_head: " << hex << pis->tstate_head << ", ";
    cout << "modules: " << hex << pis->modules << ", ";
    cout << "modules_by_index: " << hex << pis->modules_by_index << ", ";
    cout << "sysdict: " << hex << pis->sysdict << ", ";
    cout << "builtins: " << hex << pis->builtins << ", ";
    cout << "importlib: " << hex << pis->importlib << ", ";
    cout << "codec_search_path: " << hex << pis->codec_search_path << ", ";
    cout << "codec_search_cache: " << hex << pis->codec_search_cache << ", ";
    cout << "codec_error_registry: " << hex << pis->codec_error_registry << ", ";
    cout << "codecs_initialized: " << hex << pis->codecs_initialized << ", ";
    cout << "fscodec_initialized: " << hex << pis->fscodec_initialized << ", ";
    cout << "builtins_copy: " << hex << pis->builtins_copy << "\n";
    cout << "-------------------------------------------------------------" << '\n';
}

static void print_thread_state(PyThreadState *pts) {
    cout << "----------------------- thread state ------------------------" << '\n';
    cout << "thread state address: " << hex << pts << ", ";
    cout << "stack frame: " << hex << pts->frame << "\n";
    cout << "-------------------------------------------------------------" << '\n';
}

static void print_stack_frame(PyFrameObject *pfs) {
    cout << "----------------------- stack frame ------------------------" << '\n';
    cout << "frame object address: " << hex << pfs << ", ";
    cout << "frame code address: " << hex << pfs->f_code << "\n";
    cout << "trace opcodes: " << hex << pfs->f_trace_opcodes << "\n";
    print_mem_content(reinterpret_cast<uint8_t *>(pfs->f_code), 64);
    reinterpret_cast<uint8_t *>(pfs->f_code)[0] = 0x55;
    print_mem_content(reinterpret_cast<uint8_t *>(pfs->f_code), 64);
    cout << "-------------------------------------------------------------" << '\n';
}

static PyObject *get_interpreter_state(PyObject *self, PyObject *args) {
    PyInterpreterState *interpreter_state = PyInterpreterState_Main();
    print_interpreter_state(interpreter_state);
    return self;
}

static PyObject *get_thread_state(PyObject *self, PyObject *args) {
    PyThreadState thread_state;
    thread_state = *PyThreadState_Get();
    print_thread_state(&thread_state);
    return self;
}

static PyObject *get_stack_frame(PyObject *self, PyObject *args) {
    PyFrameObject stack_frame;
    stack_frame = *PyThreadState_Get()->frame;
    print_stack_frame(&stack_frame);
    return self;
}

static PyMethodDef pyternals_meth[] = {
        {"print_basic_info", print_basic_info, METH_VARARGS, "Get the python3.8 interpreter basic info"},
        {"get_thread_state", get_thread_state, METH_VARARGS, "Get the python3.8 thread state data"},
        {"get_interpreter_state", get_interpreter_state, METH_VARARGS, "Get the python3.8 interpreter state data"},
        {"get_stack_frame", get_stack_frame, METH_VARARGS, "Get the python3.8 current stack frame"},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pyternals_module = {
        PyModuleDef_HEAD_INIT,
        "pyternals",
        "Get the python3.8 thread and interpreter state data",
        -1,
        pyternals_meth
};

extern "C" PyMODINIT_FUNC PyInit_pyternals(void) {
    return PyModule_Create(&pyternals_module);
}
