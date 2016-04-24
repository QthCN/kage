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
