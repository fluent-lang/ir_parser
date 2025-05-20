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

#ifndef PARSER_VAR_H
#define PARSER_VAR_H
#include <memory>

#include "../../ast/ast.h"
#include "../../../lexer/token.h"
#include "../identifier/identifier.h"

namespace fluent::parser
{
    inline void parse_var(
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast,
        const Rule rule,
        const bool do_parse_type,
        const bool do_parse_expr
    )
    {
        // Create a new AST node
        const auto var = std::make_shared<AST>();
        var->rule = rule;
        var->value = std::nullopt;
        var->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

        // Parse the name
        const auto name = parse_identifier(tokens);
        var->children->push_back(name);

        // Parse the type if needed
        if (do_parse_type)
        {
            parse_type(tokens, var);
        }

        if (do_parse_expr)
        {
            tokens->next();
            // Parse the expression
            parse_expr(tokens, var, "var");
        }

        // Add the var node to the AST
        ast->children->push_back(var);
    }
}

#endif //PARSER_VAR_H
