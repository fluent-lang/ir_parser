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

#ifndef PARSER_BINARY_H
#define PARSER_BINARY_H
#include <memory>
#include "../identifier/identifier.h"
#include "../../ast/ast.h"
#include "../../../lexer/token.h"

namespace fluent::parser
{
    inline void parse_singly_opt(
    token::TokenStream *tokens,
    const std::shared_ptr<AST> &ast,
    const Rule rule
)
    {
        // Create a new AST node
        const std::shared_ptr<AST> node = create_node(rule);

        // Parse two identifiers for the operands
        node->children->push_back(parse_identifier(tokens));

        // Add the binary node to the AST
        ast->children->push_back(node);
    }

    inline bool process_possible_num(
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &node
    )
    {
        // Check if we have integer literals
        if (tokens->peek()->type == token::NumLiteral)
        {
            // Get the next token
            const auto next = util::try_unwrap(tokens->next());
            util::assert_eq(next.type, token::NumLiteral);

            // Create a new literal node
            const auto literal = std::make_shared<AST>();
            literal->rule = NumLiteral;
            literal->value = next.value;
            literal->children = std::nullopt;

            // Add the literal node to the AST
            node->children->push_back(literal);
            return true;
        }

        return false;
    }

    inline void parse_binary_opt(
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast,
        const Rule rule
    )
    {
        // Create a new AST node
        const std::shared_ptr<AST> node = create_node(rule);

        // Parse 2 operands for the binary operation
        for (int i = 0; i < 2; ++i)
        {
            // Check if we have integer literals
            if (!process_possible_num(tokens, node))
            {
                // Parse an identifier for the operand
                node->children->push_back(parse_identifier(tokens));
            }
        }

        // Add the binary node to the AST
        ast->children->push_back(node);
    }
}

#endif //PARSER_BINARY_H
