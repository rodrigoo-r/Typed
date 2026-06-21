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
use crate::adt::lang::AST;
use crate::adt::result::RuntimeResult;
use crate::adt::runtime::{Float, HashableObject, NonHashableObject, Object, RuntimeDictionary, RuntimeList, StringKind};
use crate::adt::runtime::Object::NonHashable;

macro_rules! unwrap_obj {
    ($obj:expr, $pattern:pat => $result:expr, $trace:expr) => {{
        if let $pattern = $obj {
            Ok($result)
        } else {
            Err(RuntimeError::mismatched_types($trace))
        }
    }}
}

pub fn get_string<'obj, 'data>(
    obj: &'obj Object<'data>,
    trace: &AST<'data>,
) -> RuntimeResult<&'obj str>
{
    let kind = unwrap_obj!(
        obj,
        Object::Hashable(HashableObject::String(s)) => s,
        trace
    )?;

    match kind {
        StringKind::Static(s) => Ok(s),
        StringKind::Dynamic(s) => Ok(s.as_str()),
    }
}

pub fn get_integer<'source>(
    obj: &Object<'source>,
    trace: &AST<'source>
) -> RuntimeResult<isize>
{
    unwrap_obj!(
        obj,
        Object::Hashable(HashableObject::Integer(s)) => s.clone(),
        trace
    )
}

pub fn get_float<'source>(
    obj: &Object<'source>,
    trace: &AST<'source>
) -> RuntimeResult<Float>
{
    unwrap_obj!(
        obj,
        Object::Hashable(HashableObject::Float(s)) => s.clone(),
        trace
    )
}

pub fn get_boolean<'source>(
    obj: &Object<'source>,
    trace: &AST<'source>
) -> RuntimeResult<bool>
{
    unwrap_obj!(
        obj,
        Object::Hashable(HashableObject::Boolean(s)) => s.clone(),
        trace
    )
}

pub fn get_list<'source>(
    obj: &Object<'source>,
    trace: &AST<'source>
) -> RuntimeResult<RuntimeList<'source>>
{
    unwrap_obj!(
        obj,
        NonHashable(NonHashableObject::List(s)) => s.clone(),
        trace
    )
}

pub fn get_dictionary<'source>(
    obj: &Object<'source>,
    trace: &AST<'source>
) -> RuntimeResult<RuntimeDictionary<'source>>
{
    unwrap_obj!(
        obj,
        NonHashable(NonHashableObject::Dictionary(s)) => s.clone(),
        trace
    )
}