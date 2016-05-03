//
// Created by thuanqin on 16/4/24.
//

#ifndef KAGE_UTILS_H
#define KAGE_UTILS_H

#include "string"
#include <map>
#include <vector>
#include <uuid/uuid.h>

#include "numpy_import.h"
#include "numpy/arrayobject.h"

std::string get_uuid();
void map_str_vector_to_npy_intp_map(std::vector<std::string> &, std::map<std::string, npy_intp> &);

#endif //KAGE_UTILS_H
