#include <iostream>
#include <vector>
#include <map>

#include "numpy_import.h"
#ifdef NO_IMPORT_ARRAY
#undef NO_IMPORT_ARRAY
#endif
#include "numpy/arrayobject.h"
#include "Python.h"

#include "datarobot2d.h"
#include "utils.h"

#define ARGS_NUM_CHECK(NUM)  if (PyTuple_GET_SIZE(cpp_args) != NUM) { \
                                 PyErr_SetString(kageext_error, "need NUM args"); \
                                 return NULL; \
                           }


const std::string EXT_VERSION = "0.1";
static PyObject *kageext_error;
static std::map<std::string, std::shared_ptr<DataRobot2D> > datarobot2ds_map;

// get cpp extension's version
static PyObject *
show_ext_version(PyObject *self, PyObject *args)
{
    return PyUnicode_FromString(EXT_VERSION.c_str());
}

static PyObject *s_parse_vector_to_pyobj(std::vector<std::string> v) {
    PyObject *pyobj = PyTuple_New(v.size());
    std::vector<std::string>::size_type index = 0;
    for (auto s : v) {
        PyObject *item = Py_BuildValue("s", s.c_str());
        PyTuple_SetItem(pyobj, index, item);
        index++;
    }
    return pyobj;
}

static std::vector<std::string> s_parse_tuple_to_vector(PyObject *tuple) {
    std::vector<std::string> result;
    if (!PyTuple_Check(tuple)) {
        PyErr_SetString(kageext_error, "Need tuple");
        return result;
    }
    auto tuple_size = PyTuple_GET_SIZE(tuple);
    for(auto i=0; i<tuple_size; i++) {
        PyObject *t_item = PyTuple_GET_ITEM(tuple, i);
        const char *t_value;
        if (!PyArg_Parse(t_item, "s", &t_value)) {
            PyErr_SetString(kageext_error, "Need string");
            return result;
        }
        result.push_back(std::string(t_value));
    }
    return result;
}

static std::shared_ptr<DataRobot2D> get_datarobot2d_from_pyobj(PyObject *id) {
    const char *datarobot2d_s;
    if(!PyArg_Parse(id, "s", &datarobot2d_s)) {
        PyErr_SetString(kageext_error, "get_datarobot2d_content with no valid obj_id");
        return NULL;
    }

    std::string datarobot2d_id(datarobot2d_s);

    if (datarobot2ds_map.find(datarobot2d_id) == datarobot2ds_map.end()) {
        PyErr_SetString(kageext_error, "no such obj_id");
        return NULL;
    }

    std::shared_ptr<DataRobot2D> dataRobot2D = datarobot2ds_map[datarobot2d_id];
    return dataRobot2D;
}

// function mapping from Python to CPP
static PyObject *
call(PyObject *self, PyObject *args)
{
    PyObject *cpp_args = nullptr;
    const char *function;
    if (!PyArg_ParseTuple(args, "sO", &function, &cpp_args)) {
        PyErr_SetString(kageext_error, "PyArg Error");
        return NULL;
    }
    if (!PyTuple_Check(cpp_args)) {
        PyErr_SetString(kageext_error, "CPP Arg not a tuple");
        return NULL;
    }

    if (strcmp(function, "create_datarobot2d") == 0) {
        // cpp_args: data(2darray), columns(list), index(list)
        PyObject *data;
        PyObject *columns;
        PyObject *index;

        ARGS_NUM_CHECK(3)

        data = PyTuple_GET_ITEM(cpp_args, 0);
        columns = PyTuple_GET_ITEM(cpp_args, 1);
        index = PyTuple_GET_ITEM(cpp_args, 2);

        std::vector<std::string> v_columns = s_parse_tuple_to_vector(columns);
        std::vector<std::string> v_index = s_parse_tuple_to_vector(index);
        if (v_columns.empty()) {
            PyErr_SetString(kageext_error, "columns is empty");
            return NULL;
        }
        if (v_index.empty()) {
            PyErr_SetString(kageext_error, "index is empty");
            return NULL;
        }

        PyArrayObject *array = (PyArrayObject *)data;
        std::shared_ptr<DataRobot2D> dataRobot2D = std::make_shared<DataRobot2D>(array, v_columns, v_index);
        std::string uuid = get_uuid();
        datarobot2ds_map[uuid] = dataRobot2D;
        return PyUnicode_FromString(uuid.c_str());
    } else if (strcmp(function, "get_datarobot2d_content") == 0) {
        PyObject *datarobot2d_id_obj;

        ARGS_NUM_CHECK(1)

        datarobot2d_id_obj = PyTuple_GET_ITEM(cpp_args, 0);
        std::shared_ptr<DataRobot2D> dataRobot2D = get_datarobot2d_from_pyobj(datarobot2d_id_obj);
        if (dataRobot2D == NULL) return NULL;

        std::vector<std::string> columns = dataRobot2D->get_columns();
        std::vector<std::string> index = dataRobot2D->get_index();
        PyObject *p_columns = s_parse_vector_to_pyobj(columns);
        PyObject *p_index = s_parse_vector_to_pyobj(index);
        PyObject *array = (PyObject *)dataRobot2D->get_array();
        return Py_BuildValue("(OOO)", array, p_columns, p_index);

    } else if (strcmp(function, "deconstruct_datarobot2d") == 0) {
        PyObject *datarobot2d_id_obj;

        ARGS_NUM_CHECK(1)

        datarobot2d_id_obj = PyTuple_GET_ITEM(cpp_args, 0);
        const char *datarobot2d_s;
        if(!PyArg_Parse(datarobot2d_id_obj, "s", &datarobot2d_s)) {
            PyErr_SetString(kageext_error, "deconstruct_datarobot2d with no valid obj_id");
            return NULL;
        }
        std::string datarobot2d_id(datarobot2d_s);
        datarobot2ds_map.erase(datarobot2d_id);

        Py_RETURN_NONE;
    } else if (strcmp(function, "get_item_by_row_type_str") == 0) {
        PyObject *datarobot2d_id_obj;
        PyObject *key;
        const char *key_str;

        ARGS_NUM_CHECK(2)

        datarobot2d_id_obj = PyTuple_GET_ITEM(cpp_args, 0);
        key = PyTuple_GET_ITEM(cpp_args, 1);
        if (!PyArg_Parse(key, "s", &key_str)) {
            PyErr_SetString(kageext_error, "PyArg Error");
            return NULL;
        }
        std::string target(key_str);
        std::shared_ptr<DataRobot2D> dataRobot2D = get_datarobot2d_from_pyobj(datarobot2d_id_obj);
        if (dataRobot2D == NULL) return NULL;
        std::shared_ptr<DataRobot2D> result = dataRobot2D->get_item_by_row_type_str(target);
        if (result == nullptr) {
            PyErr_SetString(PyExc_KeyError, "No such key");
            return NULL;
        }
        std::string uuid = get_uuid();
        datarobot2ds_map[uuid] = result;
        return PyUnicode_FromString(uuid.c_str());
    } else if (strcmp(function, "str") == 0) {
        PyObject *datarobot2d_id_obj;

        ARGS_NUM_CHECK(1)

        datarobot2d_id_obj = PyTuple_GET_ITEM(cpp_args, 0);
        std::shared_ptr<DataRobot2D> dataRobot2D = get_datarobot2d_from_pyobj(datarobot2d_id_obj);
        std::shared_ptr<std::string> result = dataRobot2D->str();
        return PyUnicode_FromString(result->c_str());
    }
    Py_RETURN_NONE;
}

static PyMethodDef KageExtMethods[] = {
        {"eversion",  show_ext_version, METH_VARARGS, "Get extension's version."},
        {"call", call, METH_VARARGS, "Function call entrance."},
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

    kageext_error = PyErr_NewException("kageext.error", NULL, NULL);
    Py_INCREF(kageext_error);
    PyModule_AddObject(m, "error", kageext_error);

    import_array();

    return m;
}