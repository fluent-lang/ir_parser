include(FetchContent)
cmake_minimum_required(VERSION 3.30)
project(fluent_parser)

FetchContent_Declare(
        unordered_dense
        GIT_REPOSITORY https://github.com/martinus/unordered_dense.git
        GIT_TAG        main
)

FetchContent_Declare(
        fluent_libc
        GIT_REPOSITORY https://github.com/rodrigoo-r/fluent_libc
        GIT_TAG        master
)

FetchContent_MakeAvailable(unordered_dense)
FetchContent_MakeAvailable(fluent_libc)

set(CMAKE_CXX_STANDARD 20)

add_library(fluent_parser STATIC
        library.cpp
        include/fluent/lexer/lexer.h
        include/fluent/lexer/token.h
        include/fluent/structure/immut_str/immut_str.h
        include/fluent/util/unwrap.h
        include/fluent/util/assert.h
        include/fluent/parser/parser.h
        include/fluent/parser/rule/link/link.h
        include/fluent/parser/rule/function/function.h
        include/fluent/parser/rule/identifier/identifier.h
        include/fluent/parser/rule/type/type.h
        include/fluent/parser/rule/reference/reference.h
        include/fluent/parser/rule/module/module.h
        include/fluent/parser/rule/ret/ret.h
        include/fluent/parser/rule/expr/expr.h
        include/fluent/parser/rule/ranged/ranged.h
        include/fluent/parser/rule/prop/prop.h
        include/fluent/parser/rule/binary/binary.h
        include/fluent/parser/rule/var/var.h
        include/fluent/parser/rule/if/if.h
        include/fluent/parser/rule/block/block.h
        include/fluent/parser/rule/pick/pick.h
        include/fluent/parser/rule/arithmetic/arithmetic.h
        include/fluent/parser/ast/ast.h
)

target_include_directories(fluent_parser PRIVATE ${CMAKE_BINARY_DIR}/_deps/unordered_dense-src/include)
target_include_directories(fluent_parser PRIVATE ${CMAKE_BINARY_DIR}/_deps/fluent_libc-src/include)
target_link_libraries(fluent_parser PRIVATE unordered_dense)
target_link_libraries(fluent_parser PRIVATE fluent_libc)