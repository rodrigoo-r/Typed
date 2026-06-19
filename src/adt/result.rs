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
use crate::adt::error::ExecutionError;
use crate::adt::runtime::Object;

pub type RuntimeResult<'a, Success> = Result<
    Success,
    ExecutionError
>;

pub type ExecutionResult<'a> =
    RuntimeResult<'a, Object<'a>>;