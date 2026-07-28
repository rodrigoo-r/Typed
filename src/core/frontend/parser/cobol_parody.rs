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

use pest_derive::Parser;
use crate::core::frontend::parser::Rule as SharedRule;

#[derive(Parser)]
#[grammar = "grammar/cobol-parody-grammar.pest"]
pub struct COBOLParodyParser;

impl From<Rule> for SharedRule {
    fn from(value: Rule) -> Self {
        match value {
            Rule::EOI => {
                SharedRule::EOI
            }

            Rule::COMMENT => {
                SharedRule::COMMENT
            }

            Rule::WHITESPACE => {
                SharedRule::WHITESPACE
            }

            Rule::Program => {
                SharedRule::Program
            }

            Rule::Top_Level => {
                SharedRule::Top_Level
            }

            Rule::Use => {
                SharedRule::Use
            }

            Rule::Identifier => {
                SharedRule::Identifier
            }

            Rule::Procedure => {
                SharedRule::Procedure
            }

            Rule::Procedure_Return_Kind => {
                SharedRule::Procedure_Return_Kind
            }

            Rule::Procedure_Arguments => {
                SharedRule::Procedure_Arguments
            }

            Rule::Declaration_Data => {
                SharedRule::Declaration_Data
            }

            Rule::String => {
                SharedRule::String
            }

            Rule::Integer => {
                SharedRule::Integer
            }

            Rule::Float => {
                SharedRule::Float
            }

            Rule::Boolean => {
                SharedRule::Boolean
            }

            Rule::List => {
                SharedRule::List
            }

            Rule::Dictionary => {
                SharedRule::Dictionary
            }

            Rule::Kind => {
                SharedRule::Kind
            }

            Rule::Body => {
                SharedRule::Body
            }

            Rule::Return => {
                SharedRule::Return
            }

            Rule::For => {
                SharedRule::For
            }

            Rule::While => {
                SharedRule::While
            }

            Rule::Declare => {
                SharedRule::Declare
            }

            Rule::If => {
                SharedRule::If
            }

            Rule::Else_If => {
                SharedRule::Else_If
            }

            Rule::Else => {
                SharedRule::Else
            }

            Rule::Condition_Group => {
                SharedRule::Condition_Group
            }

            Rule::Expression => {
                SharedRule::Expression
            }

            Rule::Greater => {
                SharedRule::Greater
            }

            Rule::Less => {
                SharedRule::Less
            }

            Rule::Equal => {
                SharedRule::Equal
            }

            Rule::Greater_Equal => {
                SharedRule::Greater_Equal
            }

            Rule::Less_Equal => {
                SharedRule::Less_Equal
            }

            Rule::And => {
                SharedRule::And
            }

            Rule::Or => {
                SharedRule::Or
            }

            Rule::Not => {
                SharedRule::Not
            }

            Rule::Call => {
                SharedRule::Call
            }

            Rule::Call_Arguments => {
                SharedRule::Call_Arguments
            }

            Rule::Add => {
                SharedRule::Add
            }

            Rule::Subtract => {
                SharedRule::Subtract
            }

            Rule::Multiply => {
                SharedRule::Multiply
            }

            Rule::Divide => {
                SharedRule::Divide
            }

            Rule::Integer_Literal => {
                SharedRule::Integer_Literal
            }

            Rule::Float_Literal => {
                SharedRule::Float_Literal
            }

            Rule::Boolean_Literal => {
                SharedRule::Boolean_Literal
            }

            Rule::True_Literal => {
                SharedRule::True_Literal
            }

            Rule::False_Literal => {
                SharedRule::False_Literal
            }

            Rule::String_Literal => {
                SharedRule::String_Literal
            }

            Rule::Single_Line_String_Char => {
                SharedRule::Single_Line_String_Char
            }

            Rule::Multi_Line_String_Char => {
                SharedRule::Multi_Line_String_Char
            }

            Rule::Escape_Sequence => {
                SharedRule::Escape_Sequence
            },
            
            _ => SharedRule::Program
        }
    }
}

pub mod grammar {
    use std::borrow::Cow;
    use std::cell::RefCell;
    use std::collections::VecDeque;
    use std::rc::Rc;
    use pest::iterators::Pairs;
    use crate::adt::lang::{ChildAST, AST};
    use crate::support::failable::catch_parse;
    use crate::support::str_conv::escape::unescape;
    use crate::convert_grammar;

    convert_grammar!(cobol_parody);
}