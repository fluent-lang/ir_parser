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

#ifndef FILE_CODE_REF_H
#define FILE_CODE_REF_H
#include "../../file_code.h"
#include "../type/type.h"

namespace fluent::file_code
{
    inline void process_ref(FileCode &result, const std::shared_ptr<parser::AST> &ast)
    {
        // Get the tree's children
        const auto children = util::try_unwrap(ast->children);

        // Get the ref's name
        const auto& name = children[0];

        // Parse the type
        const auto type = process_type(children[1]);

        // Create a result
        const auto reference = std::make_shared<Reference>();
        reference->type = type;
        reference->value = children[2];

        // Insert the reference into the result
        result.refs[name->value.value()] = reference;
    }
}

#endif //FILE_CODE_REF_H
