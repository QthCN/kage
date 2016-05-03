//
// Created by thuanqin on 16/4/24.
//

#include "utils.h"

std::string get_uuid() {
    uuid_t uuid;
    uuid_generate_random (uuid);
    char s[37];
    uuid_unparse (uuid, s);
    return std::string(s);
}

void map_str_vector_to_npy_intp_map(std::vector<std::string> & v, std::map<std::string, npy_intp> & m) {
    auto v_size = v.size();
    m.clear();
    npy_intp offset = 0;
    for (decltype(v_size) idx=0; idx<v_size; idx++) {
        m[v[idx]] = offset++;
    }
}
