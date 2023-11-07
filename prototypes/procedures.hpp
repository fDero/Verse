#pragma once
#include "../include/verse.hpp"

/*
** by including this file, you are including every possible prototype in the project
** doing as such its supposed to be temporary during a refactoring. You should never
** leave this include in the final result because it makes unclear wich module depends
** on wich other module and therefore makes it harder to spot mistakes in code structure
*/

#include "errors_prototypes.hpp"
#include "commandline_prototypes.hpp"
#include "lexing_prototypes.hpp"
#include "parsing_prototypes.hpp"
#include "serialization_prototypes.hpp"
#include "preprocessing_prototypes.hpp"
#include "generics_prototypes.hpp"
#include "scoping_prototypes.hpp"
#include "interpreter_prototypes.hpp"
#include "typesystem_prototypes.hpp"