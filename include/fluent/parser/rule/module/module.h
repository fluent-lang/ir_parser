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
// Created by rodrigo on 5/16/25.
//

#ifndef PARSER_MODULE_H
#define PARSER_MODULE_H

#include <memory>
#include <vector>
#include "../../ast/ast.h"
#include "../../../lexer/token.h"
#include "../../../util/assert.h"
#include "../identifier/identifier.h"
#include "../type/type.h"

namespace fluent::parser
{
    inline void parse_mod(
    const std::vector<std::shared_ptr<AST>> &blocks,
    token::TokenStream *tokens,
    const std::shared_ptr<AST> &ast
)
    {
        // Ensure we don't have any blocks
        util::assert_eq(blocks.empty(), true);

        // Create a new module node
        const auto mod = std::make_shared<AST>();
        mod->rule = Mod;
        mod->value = std::nullopt;
        mod->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

        // Parse the module's name
        const auto name = parse_identifier(tokens);
        mod->children->push_back(name);

        // Parse the types
        while (true)
        {
            // Break if we find an end module token
            if (
                const token::Token peek = util::try_unwrap(tokens->peek());
                peek.type == token::EndModule
            )
            {
                // Consume the end token
                tokens->next();
                break;
            }

            // Parse the type
            parse_type(tokens, mod);
        }

        // Add the module to the AST
        ast->children->push_back(mod);
    }
}

#endif //PARSER_MODULE_H
