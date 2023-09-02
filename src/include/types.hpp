#pragma once
#include "verse.hpp"

struct BaseType; struct Pointer;
struct NestedType; struct Array;

using TypeSignature = std::variant<
    BaseType,
    Pointer,
    Array,
    NestedType
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

struct NestedType {
    std::shared_ptr<TypeSignature> left;
    std::shared_ptr<TypeSignature> right;
};