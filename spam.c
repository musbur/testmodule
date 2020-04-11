#include <Python.h>

typedef struct {
     PyObject_HEAD
} Spam;

static PyObject *new(PyTypeObject *type,
         PyObject *args, PyObject *kw) {
     Spam *self;

     self = (Spam *) type->tp_alloc(type, 0);
     fprintf(stderr, "New Spam at %p\n", self);
     return (PyObject*)self;
}

static int init(Spam *self, PyObject *args, PyObject *kw) {
     fprintf(stderr, "Init Spam at %p\n", self);
     return 0;
}

static void finalize(PyObject *self) {
     fprintf(stderr, "Finalize Spam at %p\n", self);
}

static PyMethodDef spam_methods[] = {
     {NULL, NULL, 0, NULL},
};

static PyTypeObject spam_type = {
     PyVarObject_HEAD_INIT(NULL, 0)
     .tp_name = "Spam",
     .tp_basicsize = sizeof(Spam),
     .tp_flags = 0
         | Py_TPFLAGS_DEFAULT
         | Py_TPFLAGS_BASETYPE,
     .tp_doc = "Spam object",
     .tp_methods = spam_methods,
     .tp_new = new,
     .tp_init = (initproc) init,
     .tp_dealloc = finalize,
};

/* To create a new Spam object directly from C */
PyObject *make_spam() {
     PyObject *spam;
     if (PyType_Ready(&spam_type) != 0) {
         Py_RETURN_NONE;
     }
     spam = PyObject_New(Spam, &spam_type);
     PyObject_Init(spam, &spam_type);
     return spam;
}

static PyMethodDef module_methods[] = {
     {"make_spam",  (PyCFunction)make_spam, METH_NOARGS,
      "Instantiate and return a new Spam object."},
     {NULL, NULL, 0, NULL}
};

static PyModuleDef spam_module = {
     PyModuleDef_HEAD_INIT,
     "spam",
     "Defines the Spam (time, value) class"
     ,
     -1,
     module_methods
};

PyMODINIT_FUNC PyInit_spam(void) {
     PyObject *m;
     m = PyModule_Create(&spam_module);
     if (PyType_Ready(&spam_type) < 0) {
         return NULL;
     }
     PyModule_AddObject(m, "Spam", (PyObject*)&spam_type);
     return m;
}
