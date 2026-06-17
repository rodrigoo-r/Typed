#include <string>
#include <string_view>
#include <vector>
#include <gtest/gtest.h>

#include "ADT/Lang/AST.h"
#include "ADT/Lang/ASTType.h"
#include "ADT/Stream/File.h"
#include "Core/Frontend/Lexer/Lexer.h"
#include "Core/Frontend/Parser/Parser.h"

namespace
{
    using namespace Typed::Core::Frontend;
    using namespace Typed::ADT::Lang;

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

    AST* Parse(std::string_view source)
    {
        auto contents = MakeInput(source);
        Lexer::Machine lexer(contents);
        auto &tokens = lexer.Lex();
        Parser::Machine parser(tokens);
        return parser.Parse();
    }
}

TEST(ParserTest, ParsesEmptyProcedure)
{
    auto root = Parse(
        "Procedure Main\n"
        "Begin\n"
        "End_Procedure"
    );

    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->type, ASTType::Root);
    ASSERT_EQ(root->children.size(), 1);

    auto proc = root->children[0];
    EXPECT_EQ(proc->type, ASTType::Procedure);
    EXPECT_EQ(TokenValue(proc->value), "Main");
    
    // Procedure should have a Body child
    ASSERT_EQ(proc->children.size(), 1);
    EXPECT_EQ(proc->children[0]->type, ASTType::Body);
}

TEST(ParserTest, ParsesProcedureWithArguments)
{
    auto root = Parse(
        "Procedure Greet With Arguments Name as String\n"
        "Begin\n"
        "End_Procedure"
    );

    ASSERT_NE(root, nullptr);
    auto proc = root->children[0];
    EXPECT_EQ(proc->type, ASTType::Procedure);
    EXPECT_EQ(TokenValue(proc->value), "Greet");

    // Children: Arguments, Body
    ASSERT_EQ(proc->children.size(), 2);
    EXPECT_EQ(proc->children[0]->type, ASTType::Arguments);
    EXPECT_EQ(proc->children[1]->type, ASTType::Body);

    auto args = proc->children[0];
    ASSERT_EQ(args->children.size(), 1);
    
    auto arg = args->children[0];
    EXPECT_EQ(arg->type, ASTType::Argument);
    ASSERT_EQ(arg->children.size(), 2);
    EXPECT_EQ(arg->children[0]->type, ASTType::Identifier);
    EXPECT_EQ(TokenValue(arg->children[0]->value), "Name");
    EXPECT_EQ(arg->children[1]->type, ASTType::String);
}

TEST(ParserTest, ParsesVariableDeclaration)
{
    auto root = Parse(
        "Procedure Test\n"
        "Begin\n"
        "    Declare Count as Integer With 10;\n"
        "End_Procedure"
    );

    ASSERT_NE(root, nullptr);
    auto body = root->children[0]->children[0];
    EXPECT_EQ(body->type, ASTType::Body);
    
    ASSERT_EQ(body->children.size(), 1);
    auto decl = body->children[0];
    EXPECT_EQ(decl->type, ASTType::Declare);
    
    // Declare children: Identifier, Type, Expression
    ASSERT_EQ(decl->children.size(), 3);
    EXPECT_EQ(decl->children[0]->type, ASTType::Identifier);
    EXPECT_EQ(TokenValue(decl->children[0]->value), "Count");
    EXPECT_EQ(decl->children[1]->type, ASTType::Integer);
    EXPECT_EQ(decl->children[2]->type, ASTType::Expression);
}

TEST(ParserTest, ParsesIfStatement)
{
    auto root = Parse(
        "Procedure Test\n"
        "Begin\n"
        "    If True Then\n"
        "    Begin\n"
        "    End_If\n"
        "End_Procedure"
    );

    ASSERT_NE(root, nullptr);
    auto body = root->children[0]->children[0];
    ASSERT_EQ(body->children.size(), 1);
    
    auto if_stmt = body->children[0];
    EXPECT_EQ(if_stmt->type, ASTType::If);
    
    // If children: Expression, Body
    ASSERT_EQ(if_stmt->children.size(), 2);
    EXPECT_EQ(if_stmt->children[0]->type, ASTType::Expression);
    EXPECT_EQ(if_stmt->children[1]->type, ASTType::Body);
}

TEST(ParserTest, ParsesForLoop)
{
    auto root = Parse(
        "Procedure Test\n"
        "Begin\n"
        "    For i as Integer In 1 To 10 Step 1 Do\n"
        "    Begin\n"
        "    End_For\n"
        "End_Procedure"
    );

    ASSERT_NE(root, nullptr);
    auto body = root->children[0]->children[0];
    ASSERT_EQ(body->children.size(), 1);
    
    auto for_stmt = body->children[0];
    EXPECT_EQ(for_stmt->type, ASTType::For);
    
    // For children: Declare, Expression (from), Expression (to), Expression (step), Body
    ASSERT_EQ(for_stmt->children.size(), 5);
    EXPECT_EQ(for_stmt->children[0]->type, ASTType::Declare);
    EXPECT_EQ(for_stmt->children[1]->type, ASTType::Expression);
    EXPECT_EQ(for_stmt->children[2]->type, ASTType::Expression);
    EXPECT_EQ(for_stmt->children[3]->type, ASTType::Expression);
    EXPECT_EQ(for_stmt->children[4]->type, ASTType::Body);
}

TEST(ParserTest, ParsesArithmeticAdd)
{
    auto root = Parse(
        "Procedure Test\n"
        "Begin\n"
        "    Add 5 To Count;\n"
        "End_Procedure"
    );

    ASSERT_NE(root, nullptr);
    auto body = root->children[0]->children[0];
    ASSERT_EQ(body->children.size(), 1);
    
    auto expr = body->children[0];
    EXPECT_EQ(expr->type, ASTType::Expression);
    ASSERT_EQ(expr->children.size(), 1);
    
    auto add = expr->children[0];
    EXPECT_EQ(add->type, ASTType::Add);
    ASSERT_EQ(add->children.size(), 2);
    EXPECT_EQ(add->children[0]->type, ASTType::Identifier);
    EXPECT_EQ(TokenValue(add->children[0]->value), "Count");
    EXPECT_EQ(add->children[1]->type, ASTType::NumberLiteral);
    EXPECT_EQ(TokenValue(add->children[1]->value), "5");
}

TEST(ParserTest, ParsesUseStatement)
{
    auto root = Parse("Use IO;");

    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->children.size(), 1);
    
    auto use = root->children[0];
    EXPECT_EQ(use->type, ASTType::Use);
    EXPECT_EQ(TokenValue(use->value), "IO");
}

TEST(ParserTest, ParsesReturnStatement)
{
    auto root = Parse(
        "Procedure Test\n"
        "Begin\n"
        "    Return 0;\n"
        "End_Procedure"
    );

    ASSERT_NE(root, nullptr);
    auto body = root->children[0]->children[0];
    ASSERT_EQ(body->children.size(), 1);
    
    auto ret = body->children[0];
    EXPECT_EQ(ret->type, ASTType::Return);
    
    // Return children: Expression
    ASSERT_EQ(ret->children.size(), 1);
    EXPECT_EQ(ret->children[0]->type, ASTType::Expression);
}

TEST(ParserTest, ParsesWhileLoop)
{
    auto root = Parse(
        "Procedure Test\n"
        "Begin\n"
        "    While True Do\n"
        "    Begin\n"
        "    End_While\n"
        "End_Procedure"
    );

    ASSERT_NE(root, nullptr);
    auto body = root->children[0]->children[0];
    ASSERT_EQ(body->children.size(), 1);
    
    auto while_stmt = body->children[0];
    EXPECT_EQ(while_stmt->type, ASTType::While);
    
    // While children: Expression, Body
    ASSERT_EQ(while_stmt->children.size(), 2);
    EXPECT_EQ(while_stmt->children[0]->type, ASTType::Expression);
    EXPECT_EQ(while_stmt->children[1]->type, ASTType::Body);
}

TEST(ParserTest, ParsesArithmeticOperations)
{
    auto root = Parse(
        "Procedure Test\n"
        "Begin\n"
        "    Subtract 10 To Count;\n"
        "    Multiply Count By 2;\n"
        "    Divide Count By 2;\n"
        "End_Procedure"
    );

    ASSERT_NE(root, nullptr);
    auto proc = root->children[0];
    auto body = proc->children[0];
    auto sub = body->children[0]->children[0];
    auto mul = body->children[1]->children[0];
    auto div = body->children[2]->children[0];
    ASSERT_EQ(body->children.size(), 3);

    EXPECT_EQ(sub->type, ASTType::Sub);
    EXPECT_EQ(mul->type, ASTType::Mul);
    EXPECT_EQ(div->type, ASTType::Div);
}
