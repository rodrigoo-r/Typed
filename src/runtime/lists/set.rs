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
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::Object;
use crate::support::runtime::object::{get_integer, get_list};

pub fn set<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let list = args.get(0).unwrap();
    let idx = args.get(2).unwrap();
    let target = args.get(1).unwrap();

    let list = get_list(list, trace)?;
    let idx = get_integer(idx, trace)?;
    let mut list = list.borrow_mut();

    if idx < 0 || idx >= list.len() as isize {
        return Err(
            RuntimeError::out_of_bounds(trace)
        );
    }
    
    list[idx as usize] = target.clone();
    Ok(Object::Void)
}