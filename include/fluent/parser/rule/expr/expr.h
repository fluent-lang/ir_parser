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

#ifndef PARSER_EXPR_H
#define PARSER_EXPR_H

#include <memory>
#include "../../../util/unwrap.h"
#include "../arithmetic/arithmetic.h"
#include "../binary/binary.h"
#include "../ranged/ranged.h"
#include "../identifier/identifier.h"
#include "../prop/prop.h"
#include "../../../lexer/token.h"
#include "../../ast/ast.h"

namespace fluent::parser::expr
{
    inline void parse_single_token(
        const token::Token &current,
        const std::shared_ptr<AST> &ast,
        const Rule rule
    )
    {
        // Create a new node
        const auto node = std::make_shared<AST>();
        node->rule = rule;
        node->value = current.value;
        node->children = std::nullopt;

        // Add the node to the AST
        ast->children->push_back(node);
    }
}

namespace fluent::parser
{
    inline void parse_expr(
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast,
        const char *trace
    )
    {
        // Get the next token
        switch (
            const token::Token next = util::try_unwrap(tokens->curr());
            next.type
        )
        {
            case token::StringLiteral:
            {
                expr::parse_single_token(next, ast, StringLiteral);
                break;
            }

            case token::NumLiteral:
            {
                expr::parse_single_token(next, ast, NumLiteral);
                break;
            }

            case token::DecLiteral:
            {
                expr::parse_single_token(next, ast, DecLiteral);
                break;
            }

            case token::Identifier:
            {
                const std::shared_ptr<AST> id = parse_identifier_cur(tokens);

                // Add the identifier to the expression node
                ast->children->push_back(id);
                break;
            }

            case token::Call:
            {
                parse_ranged_op(tokens, ast, false, false);
                break;
            }

            case token::Construct:
            {
                parse_ranged_op(tokens, ast, true, false);
                break;
            }

            case token::Array:
            {
                parse_ranged_op(tokens, ast, false, true);
                break;
            }

            case token::Property:
            {
                parse_prop(tokens, ast);
                break;
            }

            case token::Add:
            {
                parse_arithmetic_op(tokens, ast, Add);
                break;
            }

            case token::Sub:
            {
                parse_arithmetic_op(tokens, ast, Sub);
                break;
            }

            case token::Mul:
            {
                parse_arithmetic_op(tokens, ast, Mul);
                break;
            }

            case token::Div:
            {
                parse_arithmetic_op(tokens, ast, Div);
                break;
            }

            case token::Take:
            {
                parse_singly_opt(tokens, ast, Take);
                break;
            }

            case token::Address:
            {
                parse_singly_opt(tokens, ast, Addr);
                break;
            }

            case token::Eq:
            {
                parse_binary_opt(tokens, ast, Eq);
                break;
            }

            case token::Ne:
            {
                parse_binary_opt(tokens, ast, Ne);
                break;
            }

            case token::Not:
            {
                parse_binary_opt(tokens, ast, Not);
                break;
            }

            case token::Gt:
            {
                parse_binary_opt(tokens, ast, Gt);
                break;
            }

            case token::Lt:
            {
                parse_binary_opt(tokens, ast, Lt);
                break;
            }

            case token::Ge:
            {
                parse_binary_opt(tokens, ast, Ge);
                break;
            }

            case token::Le:
            {
                parse_binary_opt(tokens, ast, Le);
                break;
            }

            case token::Or:
            {
                parse_binary_opt(tokens, ast, Or);
                break;
            }

            case token::And:
            {
                parse_binary_opt(tokens, ast, And);
                break;
            }

            default:
            {
                puts(trace);
                throw std::runtime_error("Invalid IR structure (expr)");
            }
        }
    }
}

#endif //PARSER_EXPR_H
