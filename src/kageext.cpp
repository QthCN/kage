#include <iostream>

#include "numpy_import.h"
#ifdef NO_IMPORT_ARRAY
#undef NO_IMPORT_ARRAY
#endif
#include "numpy/arrayobject.h"
#include "Python.h"


const std::string EXT_VERSION = "0.1";

// get cpp extension's version
static PyObject *
show_ext_version(PyObject *self, PyObject *args)
{
    return PyUnicode_FromString(EXT_VERSION.c_str());
}

static PyMethodDef KageExtMethods[] = {
        {"eversion",  show_ext_version, METH_VARARGS, "Get extension's version."},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef kageextmodule = {
        PyModuleDef_HEAD_INIT,
        "kageext",
        NULL,
        -1,
        KageExtMethods
};

PyMODINIT_FUNC
PyInit_kageext(void)
{
    PyObject *m;

    m = PyModule_Create(&kageextmodule);
    if (m == NULL)
        return NULL;

    import_array();

    return m;
}