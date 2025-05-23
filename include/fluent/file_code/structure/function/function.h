/*
    The Fluent Programming Language
    -----------------------------------------------------
    This code is released under the GNU GPL v3 license.
    For more information, please visit:
    https://www.gnu.org/licenses/gpl-3.0.html
    -----------------------------------------------------
    Copyright (c) 2025 Rodrigo R. & All Fluent Contributors
    This program comes with ABSOLUTELY NO WARRANTY.
    For details type `fluent l`. This is free software,
    and you are welcome to redistribute it under certain
    conditions; type `fluent l -f` for details.
*/

//
// Created by rodrigo on 5/18/25.
//

#ifndef FILE_CODE_STRUCTURE_FUNCTION_H
#define FILE_CODE_STRUCTURE_FUNCTION_H
#include <ankerl/unordered_dense.h>

#include "../../../parser/parser.h"
#include "../../../structure/immut_str/immut_str.h"
#include "../../type/type_wrapper.h"

namespace fluent::file_code
{
    typedef struct
    {
        ankerl::unordered_dense::map<std::string_view, Type, ImmutStrHash, ImmutStrEqual> params;
        std::shared_ptr<parser::AST> body;
        ankerl::unordered_dense::map<std::string_view, std::shared_ptr<parser::AST>, ImmutStrHash, ImmutStrEqual> blocks;
        Type return_type;
    } Function;
}

#endif //FILE_CODE_STRUCTURE_FUNCTION_H
