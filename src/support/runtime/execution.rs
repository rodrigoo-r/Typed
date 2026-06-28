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
use crate::adt::result::{ExecutionInstruction, ExecutionTupleResult};
use crate::adt::runtime::Object;

#[macro_export]
macro_rules! execute_or_return {
    ($expr:expr) => {{
        let (res, instruction) = $expr?;
        
        if instruction == crate::adt::result::ExecutionInstruction::Stop {
            return stop_execution(res);
        }
    }}
}

pub fn stop_execution(
    res: Object
) -> ExecutionTupleResult {
    Ok((
        res,
        ExecutionInstruction::Stop
    ))
}

pub fn continue_execution(
    res: Object
) -> ExecutionTupleResult {
    Ok((
        res,
        ExecutionInstruction::Continue
    ))
}