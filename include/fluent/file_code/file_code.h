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
// Created by rodrigo on 5/18/25.
//

#ifndef FILE_CODE_H
#define FILE_CODE_H
#include <memory>
#include <ankerl/unordered_dense.h>
#include "structure/function/function.h"
#include "structure/mod/mod.h"
#include "structure/ref/ref.h"

namespace fluent::file_code
{
    typedef struct
    {
        ankerl::unordered_dense::map<std::string_view, std::shared_ptr<Reference>> refs;
        ankerl::unordered_dense::map<std::string_view, std::shared_ptr<Function>> functions;
        ankerl::unordered_dense::map<std::string_view, std::shared_ptr<Mod>> mods;
        std::vector<std::string_view> links;
    } FileCode;
}

#endif //FILE_CODE_H
