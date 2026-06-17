/*
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #                           Typed                     # *
 * #                   A text formatting DSL             # *
 * #                                                     # *
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #         Created by Rodrigo R. & Contributors        # *
 * #         Released under the Apache License 2.0       # *
 * #            Check LICENSE.MD for more info           # *
 * #                                                     # *
 * #-----------------------------------------------------# *
*/

//
// Created by Rodrigo on 5/30/26.
//

#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

#include "ADT/Exception/UnknownToken.h"
#include "ADT/Exception/UnterminatedString.h"
#include "ADT/Lang/TokenType.h"
#include "ADT/Stream/File.h"
#include "Core/Frontend/Lexer/Lexer.h"

namespace
{
    using TokenType =
        Typed::ADT::Lang::TokenType;

    struct ObservedToken
    {
        TokenType type;
        std::string value;
        size_t line;
        size_t column;
    };

    Typed::ADT::Stream::FileView MakeInput(std::string_view source)
    {
        return {source.data(), source.size()};
    }

    std::string TokenValue(const std::string_view &value)
    {
        return {
            value.data(),
            value.size()
        };
    }

    std::vector<ObservedToken> Lex(std::string_view source)
    {
        auto input = MakeInput(source);
        Typed::Core::Frontend::Lexer::Machine lexer(input);
        auto &tokens = lexer.Lex();

        std::vector<ObservedToken> observed;
        observed.reserve(tokens.size());

        for (auto i = 0u; i < tokens.size(); i++)
        {
            auto &token = tokens[i];
            observed.push_back(
                {
                    token.type,
                    TokenValue(token.value),
                    token.line,
                    token.column
                }
            );
        }

        return observed;
    }
}

TEST(LexerTest, LexesKeywordsIdentifiersLiteralsAndPunctuation)
{
    auto tokens = Lex(
        "Use IO;\n"
        "Declare Count as Integer With 42;\n"
        "Declare Ratio as Float With 3.14;\n"
        "Declare Greeting as String With \"Hello Typed\";"
    );

    std::vector<ObservedToken> expected = {
        {TokenType::Use, "", 1, 1},
        {TokenType::Identifier, "IO", 1, 5},
        {TokenType::Semicolon, "", 1, 7},
        {TokenType::Declare, "", 2, 1},
        {TokenType::Identifier, "Count", 2, 9},
        {TokenType::As, "", 2, 15},
        {TokenType::Integer, "", 2, 18},
        {TokenType::With, "", 2, 26},
        {TokenType::NumberLiteral, "42", 2, 31},
        {TokenType::Semicolon, "", 2, 33},
        {TokenType::Declare, "", 3, 1},
        {TokenType::Identifier, "Ratio", 3, 9},
        {TokenType::As, "", 3, 15},
        {TokenType::Float, "", 3, 18},
        {TokenType::With, "", 3, 24},
        {TokenType::FloatLiteral, "3.14", 3, 29},
        {TokenType::Semicolon, "", 3, 33},
        {TokenType::Declare, "", 4, 1},
        {TokenType::Identifier, "Greeting", 4, 9},
        {TokenType::As, "", 4, 18},
        {TokenType::String, "", 4, 21},
        {TokenType::With, "", 4, 28},
        {TokenType::StringLiteral, "Hello Typed", 4, 33},
        {TokenType::Semicolon, "", 4, 46}
    };

    ASSERT_EQ(tokens.size(), expected.size());
    for (auto i = 0u; i < expected.size(); i++)
    {
        EXPECT_EQ(tokens[i].type, expected[i].type) << "token " << i;
        EXPECT_EQ(tokens[i].value, expected[i].value) << "token " << i;
        EXPECT_EQ(tokens[i].line, expected[i].line) << "token " << i;
        EXPECT_EQ(tokens[i].column, expected[i].column) << "token " << i;
    }
}

TEST(LexerTest, SkipsCommentsAndLexesComparisonOperators)
{
    auto tokens = Lex(
        "# ignored\n"
        "If Count >= 10 And Count <= 20 Or Count == 30 Then\n"
        "    Count > 0, Count < 99;"
    );

    std::vector<TokenType> expected_types = {
        TokenType::If,
        TokenType::Identifier,
        TokenType::GreaterEqual,
        TokenType::NumberLiteral,
        TokenType::And,
        TokenType::Identifier,
        TokenType::LessEqual,
        TokenType::NumberLiteral,
        TokenType::Or,
        TokenType::Identifier,
        TokenType::Equal,
        TokenType::NumberLiteral,
        TokenType::Then,
        TokenType::Identifier,
        TokenType::Greater,
        TokenType::NumberLiteral,
        TokenType::Comma,
        TokenType::Identifier,
        TokenType::Less,
        TokenType::NumberLiteral,
        TokenType::Semicolon
    };

    ASSERT_EQ(tokens.size(), expected_types.size());
    for (auto i = 0u; i < expected_types.size(); i++)
    {
        EXPECT_EQ(tokens[i].type, expected_types[i]) << "token " << i;
    }

    EXPECT_EQ(tokens[0].line, 2);
    EXPECT_EQ(tokens[0].column, 1);
    EXPECT_EQ(tokens[13].line, 3);
    EXPECT_EQ(tokens[13].column, 5);
}

TEST(LexerTest, RejectsMalformedFloatLiterals)
{
    auto input = MakeInput("Declare Ratio as Float With 3.14.15;");
    Typed::Core::Frontend::Lexer::Machine lexer(input);

    EXPECT_THROW(
        lexer.Lex(),
        Typed::ADT::Exception::UnknownToken
    );
}

TEST(LexerTest, RejectsUnterminatedStringLiterals)
{
    auto input = MakeInput("Declare Message as String With \"Hello\n");
    Typed::Core::Frontend::Lexer::Machine lexer(input);

    EXPECT_THROW(
        lexer.Lex(),
        Typed::ADT::Exception::UnterminatedString
    );
}