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

namespace parser::expr
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

namespace parser
{
    inline void parse_expr(
        token::TokenStream *tokens,
        const std::shared_ptr<AST> &ast,
        const char *trace
    )
    {
        // Create a new expression node
        const auto expr = std::make_shared<AST>();
        expr->rule = Expression;
        expr->value = std::nullopt;
        expr->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

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
                expr->children->push_back(id);
                break;
            }

            case token::Call:
            {
                parse_ranged_op(tokens, expr, false, false);
                break;
            }

            case token::Construct:
            {
                parse_ranged_op(tokens, expr, true, false);
                break;
            }

            case token::Array:
            {
                parse_ranged_op(tokens, expr, false, true);
                break;
            }

            case token::Property:
            {
                parse_prop(tokens, expr);
                break;
            }

            case token::Add:
            {
                parse_arithmetic_op(tokens, expr, Add);
                break;
            }

            case token::Sub:
            {
                parse_arithmetic_op(tokens, expr, Sub);
                break;
            }

            case token::Mul:
            {
                parse_arithmetic_op(tokens, expr, Mul);
                break;
            }

            case token::Div:
            {
                parse_arithmetic_op(tokens, expr, Div);
                break;
            }

            case token::Take:
            {
                parse_singly_opt(tokens, expr, Take);
                break;
            }

            case token::Address:
            {
                parse_singly_opt(tokens, expr, Addr);
                break;
            }

            case token::Eq:
            {
                parse_binary_opt(tokens, expr, Eq);
                break;
            }

            case token::Ne:
            {
                parse_binary_opt(tokens, expr, Ne);
                break;
            }

            case token::Not:
            {
                parse_binary_opt(tokens, expr, Not);
                break;
            }

            case token::Gt:
            {
                parse_binary_opt(tokens, expr, Gt);
                break;
            }

            case token::Lt:
            {
                parse_binary_opt(tokens, expr, Lt);
                break;
            }

            case token::Ge:
            {
                parse_binary_opt(tokens, expr, Ge);
                break;
            }

            case token::Le:
            {
                parse_binary_opt(tokens, expr, Le);
                break;
            }

            default:
            {
                puts(trace);
                throw std::runtime_error("Invalid IR structure (expr)");
            }
        }

        // Add the expression node to the AST
        ast->children->push_back(expr);
    }
}

#endif //PARSER_EXPR_H
