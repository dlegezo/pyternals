#define PY_SSIZE_T_CLEAN

#include "/usr/include/python3.8/Python.h"
#include <iostream>
#include <vector>

using namespace std;

typedef vector<uint8_t> storage;
typedef vector<uint8_t>::iterator storage_it;

typedef struct _is {
    struct _is *next;
    struct _ts *tstate_head;

    PyObject *modules;
    PyObject *modules_by_index;
    PyObject *sysdict;
    PyObject *builtins;
    PyObject *importlib;

    PyObject *codec_search_path;
    PyObject *codec_search_cache;
    PyObject *codec_error_registry;
    int codecs_initialized;
    int fscodec_initialized;

    PyObject *builtins_copy;
    } PyInterpreterState;

//struct _ts {
//    struct _ts *prev;
//    struct _ts *next;
//    PyInterpreterState *interp;
//    struct _frame *frame;
//    int recursion_depth;
//    char overflowed;
//    char recursion_critical;
//    int stackcheck_counter;
//    int tracing;
//    int use_tracing;
//    Py_tracefunc c_profilefunc;
//    Py_tracefunc c_tracefunc;
//    PyObject *c_profileobj;
//    PyObject *c_traceobj;
//    PyObject *curexc_type;
//    PyObject *curexc_value;
//    PyObject *curexc_traceback;
//    _PyErr_StackItem exc_state;
//    _PyErr_StackItem *exc_info;
//    PyObject *dict;  /* Stores per-thread state */
//    int gilstate_counter;
//    PyObject *async_exc; /* Asynchronous exception to raise */
//    unsigned long thread_id; /* Thread id where this tstate was created */
//    int trash_delete_nesting;
//    PyObject *trash_delete_later;
//    void (*on_delete)(void *);
//    void *on_delete_data;
//    int coroutine_origin_tracking_depth;
//    PyObject *async_gen_firstiter;
//    PyObject *async_gen_finalizer;
//    PyObject *context;
//    uint64_t context_ver;
//    /* Unique thread state id. */
//    uint64_t id;
//};

static void print_mem_content(uint8_t *m) {
    for (int i=0; i<32; ++i) {
        cout << hex << (int)m[i] << " ";
    }
    cout << endl;
}

static PyObject *print_basic_info(PyObject *self, PyObject *args) {
    cout << "version: " << Py_GetVersion() << ", ";
    cout << "platform: " << Py_GetPlatform() << ", ";
    cout << "compiler: " << Py_GetCompiler() << ", ";
    cout << "build: " << Py_GetBuildInfo() << ", ";
    return self;
}

static PyObject *get_interpreter_state(PyObject *self, PyObject *args) {
    PyInterpreterState *interpreter_state = PyInterpreterState_Main();
    cout << "interpreters list main elem address: " << hex << &interpreter_state << "\n";
    cout << "thread state address: " << hex << interpreter_state->tstate_head << "\n";
    cout << "interpreters list next elem address: " << hex << interpreter_state->next << "\n";
    return self;
}

static PyObject *get_thread_state(PyObject *self, PyObject *args) {
    PyThreadState thread_state;
    storage vi(12);
    thread_state = *PyThreadState_Get();
    cout << "thread state address: " << &thread_state << "\n";
    cout << "prev: " << hex << thread_state.prev << "\n";
    cout << "next: " << hex << thread_state.next << "\n";
    cout << "interp: " << hex << thread_state.interp << "\n";
    cout << "frame: " << hex << thread_state.frame << "\n";
    print_mem_content((uint8_t *)&thread_state);
    return self;
}

static PyMethodDef pyternals_meth[] = {
        {"print_basic_info", print_basic_info, METH_VARARGS, "Get the python3.8 interpreter basic info"},
        {"get_thread_state", get_thread_state, METH_VARARGS, "Get the python3.8 thread state data"},
        {"get_interpreter_state", get_interpreter_state, METH_VARARGS, "Get the python3.8 interpreter state data"},
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
