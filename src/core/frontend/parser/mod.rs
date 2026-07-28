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
pub mod convert;
pub mod standard;
pub mod old;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum Rule {
    EOI,
    COMMENT,
    WHITESPACE,
    Program,
    Top_Level,
    Use,
    Identifier,
    Procedure,
    Procedure_Return_Kind,
    Procedure_Arguments,
    Declaration_Data,
    String,
    Integer,
    Float,
    Boolean,
    List,
    Dictionary,
    Kind,
    Body,
    Return,
    For,
    While,
    Declare,
    If,
    Else_If,
    Else,
    Condition_Group,
    Expression,
    Greater,
    Less,
    Equal,
    Greater_Equal,
    Less_Equal,
    And,
    Or,
    Not,
    Call,
    Call_Arguments,
    Add,
    Subtract,
    Multiply,
    Divide,
    Integer_Literal,
    Float_Literal,
    Boolean_Literal,
    True_Literal,
    False_Literal,
    String_Literal,
    Single_Line_String_Char,
    Multi_Line_String_Char,
    Escape_Sequence
}