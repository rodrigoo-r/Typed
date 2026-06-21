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
pub enum ParseErrorKind {
    MalformedEscapeSequence,
}

#[derive(Debug)]
pub struct ParseError {
    pub kind : ParseErrorKind,
    pub message : &'static str,
    pub line: usize,
    pub column: usize
}

#[derive(Debug)]
pub enum RuntimeErrorKind {
    UndefinedFindProcedure,
    MismatchedTypes,
    MismatchedArgumentCount,
    OutOfBounds,
    CouldNotFindLibrary,
    MalformedLiteral,
    UndefinedSymbol,
    InvalidLoopVariable,
    InvalidLoopStep,
    CouldNotRead,
}

#[derive(Debug)]
pub struct RuntimeError {
    pub kind : RuntimeErrorKind,
    pub message : &'static str,
    pub line: usize,
    pub column: usize
}

impl RuntimeError {
    fn create(
        trace: &AST,
        kind: RuntimeErrorKind,
        message: &'static str
    ) -> Self {
        RuntimeError{
            kind,
            message,
            line: trace.line,
            column: trace.column
        }
    }

    pub fn undefined_procedure(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            RuntimeErrorKind::UndefinedFindProcedure,
            "Undefined procedure"
        )
    }

    pub fn mismatched_types(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            RuntimeErrorKind::MismatchedTypes,
            "Mismatched types"
        )
    }

    pub fn mismatched_argument_count(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            RuntimeErrorKind::MismatchedArgumentCount,
            "Mismatched argument count"
        )
    }

    pub fn out_of_bounds(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            RuntimeErrorKind::OutOfBounds,
            "Out of bounds"
        )
    }

    pub fn could_not_find_library(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            RuntimeErrorKind::CouldNotFindLibrary,
            "Could not find library"
        )
    }

    pub fn malformed_literal(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            RuntimeErrorKind::MalformedLiteral,
            "Malformed literal"
        )
    }

    pub fn undefined_symbol(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            RuntimeErrorKind::UndefinedSymbol,
            "Undefined symbol"
        )
    }

    pub fn invalid_loop_variable(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            RuntimeErrorKind::InvalidLoopVariable,
            "Invalid loop variable type, expected Integer or Float"
        )
    }

    pub fn invalid_loop_step(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            RuntimeErrorKind::InvalidLoopStep,
            "Invalid loop step"
        )
    }

    pub fn could_not_read(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            RuntimeErrorKind::CouldNotRead,
            "Could not read from stream"
        )
    }
}

impl ParseError {
    fn create(
        line: usize,
        column: usize,
        kind: ParseErrorKind,
        message: &'static str
    ) -> Self {
        ParseError{
            kind,
            message,
            line,
            column
        }
    }
    
    pub fn invalid_escape_sequence(line: usize, column: usize) -> Self {
        ParseError::create(
            line,
            column,
            ParseErrorKind::MalformedEscapeSequence,
            "Invalid escape sequence"
        )
    }
}