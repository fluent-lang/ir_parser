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

#ifndef PARSER_RANGED_H
#define PARSER_RANGED_H
#include <memory>

#include "../../ast/ast.h"
#include "../../../lexer/token.h"
#include "../../../util/assert.h"
#include "../../../util/unwrap.h"
#include "../identifier/identifier.h"

namespace fluent::parser
{
    inline void parse_ranged_op(
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast,
        const bool is_co,
        const bool is_arr
    )
    {
        // Create a new AST node
        const auto op = std::make_shared<AST>();
        op->rule = is_arr ? Array :
            is_co ? Construct
                : Call;
        op->value = std::nullopt;
        op->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

        // Parse the array length
        if (is_arr)
        {
            // Get the next token
            const auto token = util::try_unwrap(tokens->next());
            util::assert(token.type, token::NumLiteral);

            // Create a new number literal node
            const auto literal = std::make_shared<AST>();
            literal->rule = NumLiteral;
            literal->value = token.value;
            literal->children = std::nullopt;

            // Add the number literal to the array
            op->children->push_back(literal);
        }
        else
        {
            // Parse the call's name
            const auto name = parse_identifier(tokens);

            // Add the name to the call
            op->children->push_back(name);
        }

        // Determine the stop rule
        const token::TokenType end_rule = is_arr ? token::EndArray :
                is_co ? token::EndCo
                        : token::EndCall;

        // Parse all the arguments
        while (true)
        {
            // Get the current token
            if (
                const auto token = util::try_unwrap(tokens->peek());
                token.type == end_rule
            )
            {
                tokens->next();
                break;
            }

            // Parse the argument as an identifiers
            std::shared_ptr<AST> id = parse_identifier(tokens);
            op->children->push_back(id);
        }

        // Add the call to the AST
        ast->children->push_back(op);

    }
}

#endif //PARSER_RANGED_H
