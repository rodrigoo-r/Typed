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
use crate::adt::error::RuntimeError;
use crate::adt::lang::{RuntimeArguments, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::object::{get_integer, get_list};

pub fn access<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let list = args.get(0).unwrap();
    let idx = args.get(1).unwrap();

    let list = get_list(list, trace)?;
    let idx = get_integer(idx, trace)?;
    
    if idx < 0 {
        return Err(
            RuntimeError::out_of_bounds(trace)
        )
    }

    let list = list.borrow();
    let value = list.get(idx as usize);

    if value.is_none() {
        return Err(
            RuntimeError::out_of_bounds(trace)
        )
    }

    continue_execution(value.unwrap().clone())
}