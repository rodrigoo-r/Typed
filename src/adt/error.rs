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
use crate::adt::runtime::Object;

#[derive(Debug)]
pub enum ErrorKind {
    UndefinedFindProcedure,
    MismatchedTypes,
    MismatchedArgumentCount,
    OutOfBounds,
    CouldNotFindLibrary,
    MisformedLiteral,
    UndefinedSymbol
}

#[derive(Debug)]
pub struct ExecutionError {
    pub kind : ErrorKind,
    pub message : &'static str,
    pub line: usize,
    pub column: usize
}