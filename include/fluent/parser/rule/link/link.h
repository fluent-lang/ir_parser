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

#ifndef PARSER_LINK_H
#define PARSER_LINK_H
#include <memory>
#include <vector>

#include "../../../lexer/token.h"
#include "../../../util/assert.h"
#include "../../../util/unwrap.h"
#include "../../ast/ast.h"

namespace fluent::parser
{
    inline void parse_link(
        const std::vector<std::shared_ptr<AST>> &blocks,
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast
    )
    {
        // Ensure we don't have any blocks
        util::assert(blocks.empty(), true);

        // Peek to the next token
        const auto token = util::try_unwrap(tokens->next());
        util::assert(token.type, token::StringLiteral);

        // Create a new literal node
        const auto literal = create_node(StringLiteral);
        literal->value = token.value;

        // Create a new AST node
        const auto node = create_node(Link);
        node->children->push_back(literal);

        // Add the node to the result
        ast->children->push_back(node);
    }
}

#endif //PARSER_LINK_H
