#include "datarobot2d.h"

PyArrayObject *DataRobot2D::get_array() {
    Py_XINCREF(array);
    return get_array_norefinc();
}

PyArrayObject *DataRobot2D::get_array_norefinc() {
    return array;
}

std::vector<std::string> DataRobot2D::get_columns() {
    return columns;
}

std::vector<std::string> DataRobot2D::get_index() {
    return index;
}

