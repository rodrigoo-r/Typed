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
use crate::adt::error::{ParseError, RuntimeError};
use crate::adt::lang::ASTValue;
use crate::adt::runtime::Object;

pub type RuntimeResult<Success> =
    Result<
        Success,
        RuntimeError
    >;

pub type ParseResult<'a> =
    Result<
        ASTValue<'a>,
        ParseError
    >;

pub type ExecutionResult<'a> =
    RuntimeResult<Object<'a>>;

#[derive(PartialEq, Eq)]
pub enum ExecutionInstruction {
    Stop,
    Continue
}

pub type SuccessTuple<'a> =
    (Object<'a>, ExecutionInstruction);

pub type ExecutionTupleResult<'a> =
    RuntimeResult<SuccessTuple<'a>>;