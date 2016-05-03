#include "datarobot2d.h"

#include <sstream>

DataRobot2D::DataRobot2D(PyArrayObject *array, std::vector<std::string> columns, std::vector<std::string> index,
                         std::map<std::string, npy_intp> index_mapping, std::map<std::string, npy_intp> columns_mappin):
                         array(array), index(index), columns(columns),
                         index_mapping(index_mapping), columns_mapping(columns_mapping) { }

DataRobot2D::DataRobot2D(PyArrayObject *array, std::vector<std::string> columns, std::vector<std::string> index):
        array(array), index(index), columns(columns) {
    Py_XINCREF(array);
    map_str_vector_to_npy_intp_map(index, index_mapping);
    map_str_vector_to_npy_intp_map(columns, columns_mapping);
}

DataRobot2D::~DataRobot2D() {
    if (array != nullptr) {
        Py_XDECREF(array);
        array = nullptr;
    }
}

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

std::shared_ptr<std::string> DataRobot2D::str() {
    std::ostringstream outputstream;
    outputstream << "columns: " << std::endl;
    for (auto s: columns) {
        outputstream << s << " ";
    }
    outputstream << std::endl << std::endl;

    outputstream << "index: " << std::endl;
    for (auto s: index) {
        outputstream << s << " ";
    }
    outputstream << std::endl << std::endl;

    outputstream << "data: " << std::endl;
    for (auto index_name: index) {
        auto index_offset = index_mapping[index_name];
        for (auto column_name: columns) {
            auto column_offset = columns_mapping[column_name];
            auto *value = PyArray_GETPTR2(array, index_offset, column_offset);
            outputstream << (char*)(value) << " ";
        }
        outputstream << std::endl;
    }

    outputstream << PyArray_TYPE(array) << std::endl;

    std::shared_ptr<std::string> result = std::make_shared<std::string>(outputstream.str());
    return result;
}

std::shared_ptr<DataRobot2D> DataRobot2D::get_item_by_row_type_str(const std::string &key) {
    std::shared_ptr<DataRobot2D> result = nullptr;
    if (std::find(index.begin(), index.end(), key) == index.end()) {
        return result;
    }

    PyArrayObject *result_array = get_array();
    std::vector<std::string> result_index = {key};
    std::vector<std::string> result_columns = columns;
    std::map<std::string, npy_intp> result_index_mapping;
    std::map<std::string, npy_intp> result_columns_mapping = columns_mapping;
    result_index_mapping[key] = index_mapping[key];
    result = std::make_shared<DataRobot2D>(result_array, result_index, result_columns,
                                           result_index_mapping, result_columns_mapping);
    return result;
}

