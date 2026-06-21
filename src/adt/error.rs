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
use crate::adt::lang::AST;

#[derive(Debug)]
pub struct ParseError {
    pub message : &'static str,
    pub line: usize,
    pub column: usize
}

#[derive(Debug)]
pub struct RuntimeError {
    pub message : &'static str,
    pub line: usize,
    pub column: usize
}

impl RuntimeError {
    fn create(
        trace: &AST,
        message: &'static str
    ) -> Self {
        RuntimeError{
            message,
            line: trace.line,
            column: trace.column
        }
    }

    pub fn undefined_procedure(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Undefined procedure"
        )
    }

    pub fn mismatched_types(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Mismatched argument count"
        )
    }

    pub fn out_of_bounds(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Out of bounds"
        )
    }

    pub fn could_not_find_library(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Could not find library"
        )
    }

    pub fn malformed_literal(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Malformed literal"
        )
    }

    pub fn mismatched_argument_count(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Mismatched argument count"
        )
    }

    pub fn undefined_symbol(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Undefined symbol"
        )
    }

    pub fn invalid_loop_variable(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Invalid loop variable type, expected Integer or Float"
        )
    }

    pub fn invalid_loop_step(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Invalid loop step"
        )
    }

    pub fn could_not_read(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Could not read from stream"
        )
    }
    
    pub fn unexpected_return(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Unexpected return"
        )
    }

    pub fn key_not_found(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Key not found"
        )
    }

    pub fn could_not_write(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            "Could not write to stream"
        )
    }
}

impl ParseError {
    fn create(
        line: usize,
        column: usize,
        message: &'static str
    ) -> Self {
        ParseError{
            message,
            line,
            column
        }
    }
    
    pub fn invalid_escape_sequence(line: usize, column: usize) -> Self {
        ParseError::create(
            line,
            column,
            "Invalid escape sequence"
        )
    }
}