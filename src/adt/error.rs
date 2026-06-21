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
pub enum ErrorKind {
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
    pub kind : ErrorKind,
    pub message : &'static str,
    pub line: usize,
    pub column: usize
}

impl RuntimeError {
    fn create(
        trace: &AST,
        kind: ErrorKind,
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
            ErrorKind::UndefinedFindProcedure,
            "Undefined procedure"
        )
    }

    pub fn mismatched_types(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            ErrorKind::MismatchedTypes,
            "Mismatched types"
        )
    }

    pub fn mismatched_argument_count(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            ErrorKind::MismatchedArgumentCount,
            "Mismatched argument count"
        )
    }

    pub fn out_of_bounds(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            ErrorKind::OutOfBounds,
            "Out of bounds"
        )
    }

    pub fn could_not_find_library(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            ErrorKind::CouldNotFindLibrary,
            "Could not find library"
        )
    }

    pub fn malformed_literal(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            ErrorKind::MalformedLiteral,
            "Malformed literal"
        )
    }

    pub fn undefined_symbol(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            ErrorKind::UndefinedSymbol,
            "Undefined symbol"
        )
    }

    pub fn invalid_loop_variable(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            ErrorKind::InvalidLoopVariable,
            "Invalid loop variable type, expected Integer or Float"
        )
    }

    pub fn invalid_loop_step(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            ErrorKind::InvalidLoopStep,
            "Invalid loop step"
        )
    }

    pub fn could_not_read(trace: &AST) -> Self {
        RuntimeError::create(
            trace,
            ErrorKind::CouldNotRead,
            "Could not read from stream"
        )
    }
}