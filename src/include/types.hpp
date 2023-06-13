#pragma once
#include "verse.hpp"

struct BaseType; struct Pointer; struct Array;
using TypeSignature = std::variant<
    BaseType,
    Pointer,
    Array
>;

struct BaseType {
    std::string base_type;
    std::vector<TypeSignature> generics;
};

struct Pointer {
    std::shared_ptr<TypeSignature> pointed;
};

struct Array {
    std::shared_ptr<TypeSignature> type;
    int length;
};