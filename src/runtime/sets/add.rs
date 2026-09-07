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
use crate::adt::lang::{RuntimeArguments, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{Object};
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::object::{get_set};

pub fn add<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let set_obj = args.get(0).unwrap();
    let key = args.get(1).unwrap();
    
    if let Object::NonHashable(_) = key {
        return continue_execution(Object::Void)
    }

    let 
        Object::Hashable(key) 
    = key else { unreachable!() };
    let set = get_set(set_obj, trace)?;

    let mut set = set.borrow_mut();
    set.insert(key.clone());

    continue_execution(Object::Void)
}