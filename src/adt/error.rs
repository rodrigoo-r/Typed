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

pub enum ErrorKind {
    CouldNotFindProcedure,
    MismatchedTypes,
    MismatchedArgumentCount,
    OutOfBounds,
}

pub struct ExecutionError {
    pub kind : ErrorKind,
    pub message : &'static str,
    pub line: usize,
    pub column: usize
}

type ExecutionResult<'a> =
    Result<Object<'a>, ExecutionError>;