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

#ifndef FILE_CODE_TYPE_H
#define FILE_CODE_TYPE_H
#include <memory>

#include "../../type/type_wrapper.h"

namespace fluent::file_code
{
    inline Type process_type(const std::shared_ptr<parser::AST>& type)
    {
        // Create a new Type object
        Type result;

        // Get the children
        const auto children = util::try_unwrap(type->children);
        util::assert_eq(children.empty(), false);

        // Parse all children
        size_t i = 0;
        std::shared_ptr<parser::AST> curr = children[i];
        const size_t max = children.size();

        while (curr->rule == parser::Pointer)
        {
            result.pointers++;
            i++;
            curr = children[i];
        }

        // Parse the base type
        if (curr->rule == parser::Identifier)
        {
            result.base_type = curr->value;
        }
        else if (curr->rule == parser::Nothing)
        {
            result.primitive = Nothing;
        }
        else if (curr->rule == parser::Number)
        {
            result.primitive = Num;
        }
        else if (curr->rule == parser::Decimal)
        {
            result.primitive = Dec;
        }
        else if (curr->rule == parser::String)
        {
            result.primitive = String;
        }

        // Parse array types
        while (i < max && children[i]->rule == parser::ArrayType)
        {
            result.arrays++;
            i++;
        }

        return result;
    }
}

#endif //FILE_CODE_TYPE_H
