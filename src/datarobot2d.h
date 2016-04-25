//
// Created by thuanqin on 16/4/22.
//

#ifndef KAGE_DATAROBOT2D_H
#define KAGE_DATAROBOT2D_H

#include <string>
#include <vector>
#include <iostream>

#include "numpy_import.h"
#include "numpy/arrayobject.h"

class DataRobot2D {
public:
    DataRobot2D(PyArrayObject *array, std::vector<std::string> columns, std::vector<std::string> index):
            array(array), index(index), columns(columns) {
        Py_XINCREF(array);
    }
    ~DataRobot2D() {
        if (array != nullptr) {
            Py_XDECREF(array);
            array = nullptr;
        }
    }

    // 获取array
    PyArrayObject *get_array();
    // 获取array,且不增加其引用计数
    PyArrayObject *get_array_norefinc();
    // 获取columns
    std::vector<std::string> get_columns();
    // 获取index
    std::vector<std::string> get_index();

private:
    PyArrayObject *array;
    std::vector<std::string> index;
    std::vector<std::string> columns;
};

#endif //KAGE_DATAROBOT2D_H
