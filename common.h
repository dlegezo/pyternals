#pragma once

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
}PyInterpreterState;

typedef struct {
    int b_type;                 /* what kind of block this is */
    int b_handler;              /* where to jump to find handler */
    int b_level;                /* value stack level to pop to */
} PyTryBlock;

typedef struct _frame {
    PyObject_VAR_HEAD
    struct _frame *f_back;      /* previous frame, or NULL */
    PyCodeObject *f_code;       /* code segment */
    PyObject *f_builtins;       /* builtin symbol table (PyDictObject) */
    PyObject *f_globals;        /* global symbol table (PyDictObject) */
    PyObject *f_locals;         /* local symbol table (any mapping) */
    PyObject **f_valuestack;    /* points after the last local */
    /* Next free slot in f_valuestack.  Frame creation sets to f_valuestack.
       Frame evaluation usually NULLs it, but a frame that yields sets it
       to the current stack top. */
    PyObject **f_stacktop;
    PyObject *f_trace;          /* Trace function */
    char f_trace_lines;         /* Emit per-line trace events? */
    char f_trace_opcodes;       /* Emit per-opcode trace events? */

    /* Borrowed reference to a generator, or NULL */
    PyObject *f_gen;

    int f_lasti;                /* Last instruction if called */
    /* Call PyFrame_GetLineNumber() instead of reading this field
       directly.  As of 2.3 f_lineno is only valid when tracing is
       active (i.e. when f_trace is set).  At other times we use
       PyCode_Addr2Line to calculate the line from the current
       bytecode index. */
    int f_lineno;               /* Current line number */
    int f_iblock;               /* index in f_blockstack */
    char f_executing;           /* whether the frame is still executing */
    PyTryBlock f_blockstack[CO_MAXBLOCKS]; /* for try and loop blocks */
    PyObject *f_localsplus[1];  /* locals+stack, dynamically sized */
} PyFrameObject;

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
