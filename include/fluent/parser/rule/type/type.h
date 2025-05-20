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

#ifndef PARSER_TYPE_H
#define PARSER_TYPE_H
#include <memory>

#include "../../../lexer/token.h"
#include "../../../util/unwrap.h"
#include "../../ast/ast.h"

namespace parser
{
    inline void parse_type(
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast
    )
    {
        // Create a new AST node
        const auto type = std::make_shared<AST>();
        type->rule = Type;
        type->value = std::nullopt;
        type->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

        // Get the next token
        auto token = util::try_unwrap(tokens->next());

        // Parse pointers
        while (token.type == token::Ampersand)
        {
            // Create a new pointer node
            auto pointer = std::make_shared<AST>();
            pointer->rule = Pointer;
            pointer->value = std::nullopt;
            pointer->children = std::nullopt;

            // Add the pointer to the type
            type->children->push_back(pointer);

            // Move to the next token
            token = util::try_unwrap(tokens->next());
        }

        // Create a new AST node for the type
        const auto type_node = std::make_shared<AST>();
        type_node->children = std::nullopt;
        type_node->value = std::nullopt;

        // Parse the raw type
        switch (token.type)
        {
            case token::Nothing:
            {
                type_node->rule = Nothing;
                break;
            }

            case token::String:
            {
                type_node->rule = String;
                break;
            }

            case token::Boolean:
            case token::Number:
            {
                type_node->rule = Number;
                break;
            }

            case token::Decimal:
            {
                type_node->rule = Decimal;
                break;
            }

            case token::Identifier:
            {
                type_node->rule = Identifier;
                type_node->value = token.value;
                break;
            }

            default:
            {
                // Report an error
                throw std::runtime_error("Invalid type");
            }
        }

        // Add the identifier to the type
        type->children->push_back(type_node);

        // Parse array types
        while (tokens->peek()->type == token::ArrayType)
        {
            // Create a new AST node for the array type
            const auto arr = std::make_shared<AST>();
            arr->rule = ArrayType;
            arr->children = std::nullopt;
            arr->value = std::nullopt;
            type->children->push_back(arr);
            tokens->next();
        }

        // Add the type to the result
        ast->children->push_back(type);
    }
}

#endif //PARSER_TYPE_H
