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

#ifndef PARSER_PROP_H
#define PARSER_PROP_H
#include <memory>

#include "../../ast/ast.h"
#include "../../../lexer/token.h"
#include "../identifier/identifier.h"

namespace parser
{
    inline void parse_prop(
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast
    )
    {
        // Create a new AST node
        const auto prop = std::make_shared<AST>();
        prop->rule = Prop;
        prop->value = std::nullopt;
        prop->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

        // Parse the identifier
        const auto identifier = parse_identifier(tokens);
        prop->children->push_back(identifier);

        // Parse a number literal
        const auto number = util::try_unwrap(tokens->next());
        util::assert(number.type, token::NumLiteral);

        // Create a new number literal node
        const auto literal = std::make_shared<AST>();
        literal->rule = NumLiteral;
        literal->value = number.value;
        literal->children = std::nullopt;
        prop->children->push_back(literal);

        // Push the prop to the AST
        ast->children->push_back(prop);
    }
}

#endif //PARSER_PROP_H
