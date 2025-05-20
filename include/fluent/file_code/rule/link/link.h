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
// Created by rodrigo on 5/20/25.
//

#ifndef FILE_CODE_LINK_H
#define FILE_CODE_LINK_H
#include "../../file_code.h"

namespace fluent::file_code
{
    inline void process_link(FileCode &result, const std::shared_ptr<parser::AST> &ast)
    {
        // Get the link's children
        const auto children = util::try_unwrap(ast->children);
        util::assert_eq(children.empty(), false);

        // Get the first child
        const auto& literal = children[0];

        // Add the link
        result.links.push_back(util::try_unwrap(literal->value));
    }
}

#endif //FILE_CODE_LINK_H
