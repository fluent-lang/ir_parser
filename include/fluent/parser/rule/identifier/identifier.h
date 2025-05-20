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

#ifndef PARSER_IDENTIFIER_H
#define PARSER_IDENTIFIER_H

#include <memory>

#include "../../../lexer/token.h"
#include "../../../util/assert.h"
#include "../../../util/unwrap.h"
#include "../../ast/ast.h"

namespace fluent::parser
{
    inline std::shared_ptr<AST> parse_identifier_cur(token::TokenStream *tokens)
    {
        // Get the current token
        const auto current = util::try_unwrap(tokens->curr());

        util::assert(current.type, token::Identifier);

        // Create a new AST node
        auto ast = std::make_shared<AST>();
        ast->rule = Identifier;
        ast->value = current.value;
        ast->children = std::nullopt;

        return ast;
    }

    inline std::shared_ptr<AST> parse_identifier(token::TokenStream *tokens)
    {
        // Get the next token
        util::try_unwrap(tokens->next());
        return parse_identifier_cur(tokens);
    }
}

#endif //PARSER_IDENTIFIER_H
