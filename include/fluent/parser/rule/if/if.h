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
// Created by rodrigo on 5/17/25.
//

#ifndef PARSER_IF_H
#define PARSER_IF_H
#include <memory>

#include "../../ast/ast.h"
#include "../identifier/identifier.h"

namespace fluent::parser
{
    inline void parse_if(
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast
    )
    {
        // Create a new AST node
        const auto node = std::make_shared<AST>();
        node->rule = If;
        node->value = std::nullopt;
        node->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

        // Parse the condition
        const auto condition_token = util::try_unwrap(tokens->next());

        // Parse the condition
        const auto condition = std::make_shared<AST>();
        condition->children = std::nullopt;

        if (condition_token.type == token::NumLiteral)
        {
            condition->rule = NumLiteral;
        } else
        {
            util::assert_eq(condition_token.type, token::Identifier);
            condition->rule = Identifier;
        }

        condition->value = condition_token.value;
        node->children->push_back(condition);

        // Parse the blocks
        node->children->push_back(parse_identifier(tokens));
        node->children->push_back(parse_identifier(tokens));

        ast->children->push_back(node);
    }
}

#endif //PARSER_IF_H
