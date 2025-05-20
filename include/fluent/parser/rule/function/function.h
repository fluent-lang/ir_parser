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

#ifndef PARSER_FUNCTION_H
#define PARSER_FUNCTION_H
#include <memory>
#include <vector>

#include "../../../lexer/token.h"
#include "../../../util/assert.h"
#include "../../../util/unwrap.h"
#include "../../ast/ast.h"
#include "../identifier/identifier.h"
#include "../type/type.h"

namespace fluent::parser
{
    inline std::shared_ptr<AST> parse_function(
        std::vector<std::shared_ptr<AST>> &blocks,
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast
    )
    {
        // Ensure we don't have any blocks
        util::assert(blocks.empty(), true);

        // Create a new function node
        const auto fn = std::make_shared<AST>();
        fn->rule = Function;
        fn->value = std::nullopt;
        fn->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

        // Get the function's name
        const auto name = parse_identifier(tokens);
        fn->children->push_back(name);

        // Parse the function's return type
        parse_type(tokens, fn);

        // Parse the function's parameters
        const auto params = std::make_shared<AST>();
        params->rule = Params;
        params->value = std::nullopt;
        params->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

        while (true)
        {
            // Stop when we find an end params token
            if (
                const token::Token peek = util::try_unwrap(tokens->peek());
                peek.type == token::EndParams
            )
            {
                // Consume the end params token
                tokens->next();
                break;
            }

            // Create a new param node
            const auto param = std::make_shared<AST>();
            param->rule = Param;
            param->value = std::nullopt;
            param->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

            // Parse the param's name
            const auto param_name = parse_identifier(tokens);
            param->children->push_back(param_name);

            // Parse the type
            parse_type(tokens, param);

            // Add the param to the params node
            params->children->push_back(param);
        }

        // Push the parameters to the function
        fn->children->push_back(params);

        // Create a new block
        const auto block = std::make_shared<AST>();
        block->rule = Block;
        block->value = std::nullopt;
        block->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

        // Push the block to the function
        fn->children->push_back(block);

        ast->children->push_back(fn);
        blocks.push_back(block);

        return fn;
    }
}

#endif //PARSER_FUNCTION_H
