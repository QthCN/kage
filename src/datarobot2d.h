//
// Created by thuanqin on 16/4/22.
//

#ifndef KAGE_DATAROBOT2D_H
#define KAGE_DATAROBOT2D_H

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "numpy_import.h"
#include "numpy/arrayobject.h"
#include "utils.h"

class DataRobot2D {
public:
    DataRobot2D(PyArrayObject *array, std::vector<std::string> columns, std::vector<std::string> index);
    DataRobot2D(PyArrayObject *array, std::vector<std::string> columns, std::vector<std::string> index,
                std::map<std::string, npy_intp> index_mapping, std::map<std::string, npy_intp> columns_mappin);
    ~DataRobot2D();

    // 获取array
    PyArrayObject *get_array();
    // 获取array,且不增加其引用计数
    PyArrayObject *get_array_norefinc();
    // 获取columns
    std::vector<std::string> get_columns();
    // 获取index
    std::vector<std::string> get_index();
    // 获取本对象的字符串标识
    std::shared_ptr<std::string> str();

    // 根据特定的关键字获取对象引用,对应python的__getitem__
    std::shared_ptr<DataRobot2D> get_item_by_row_type_str(const std::string &key);

private:
    PyArrayObject *array;
    std::vector<std::string> index;
    std::vector<std::string> columns;
    std::map<std::string, npy_intp> index_mapping;
    std::map<std::string, npy_intp> columns_mapping;
};

#endif //KAGE_DATAROBOT2D_H
