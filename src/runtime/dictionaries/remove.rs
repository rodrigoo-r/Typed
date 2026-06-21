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
use crate::support::runtime::object::get_dictionary;

pub fn remove<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let dict_obj = args.get(0).unwrap();
    let key = args.get(1).unwrap();
    
    if let Object::NonHashable(_) = key {
        return Err(
            RuntimeError::key_not_found(trace)
        );
    }

    let 
        Object::Hashable(key) 
    = key else { unreachable!() };
    let dict = get_dictionary(dict_obj, trace)?;

    let mut dict = dict.borrow_mut();
    dict.remove(&key);
    
    Ok(Object::Void)
}