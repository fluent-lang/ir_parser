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

#ifndef PARSER_PICK_H
#define PARSER_PICK_H
#include <memory>

#include "../../ast/ast.h"
#include "../../../lexer/token.h"
#include "../binary/binary.h"

namespace fluent::parser
{
    inline void parse_pick(
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast
    )
    {
        // Create a new pick node
        const auto pick = std::make_shared<AST>();
        pick->rule = Pick;
        pick->children = std::make_optional(std::vector<std::shared_ptr<AST>>());
        pick->value = std::nullopt;

        // Parse two binary opts
        parse_binary_opt(tokens, pick, PickOpt);
        parse_binary_opt(tokens, pick, PickOpt);

        // Add the pick node to the AST
        ast->children->push_back(pick);
    }
}

#endif //PARSER_PICK_H
