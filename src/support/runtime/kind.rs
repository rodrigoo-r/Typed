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
use crate::adt::lang::{Kind, AST};
use crate::adt::result::RuntimeResult;
use crate::adt::runtime::{HashableObject, NonHashableObject, Object};

pub fn check_kind<'a>(
    expected: Kind,
    actual: &Object<'a>,
    trace: &AST
) -> RuntimeResult<'a, ()> {
    match expected {
        Kind::String => {
            if let Object::Hashable(HashableObject::String(_)) = *actual {
                return Ok(());
            }
        }

        Kind::Integer => {
            if let Object::Hashable(HashableObject::Integer(_)) = *actual {
                return Ok(());
            }
        }

        Kind::Boolean => {
            if let Object::Hashable(HashableObject::Boolean(_)) = *actual {
                return Ok(());
            }
        }

        Kind::Float => {
            if let Object::Hashable(HashableObject::Float(_)) = *actual {
                return Ok(());
            }
        }

        Kind::Dictionary => {
            if let Object::NonHashable(NonHashableObject::Dictionary(_)) = *actual {
                return Ok(());
            }
        }

        Kind::List => {
            if let Object::NonHashable(NonHashableObject::List(_)) = *actual {
                return Ok(());
            }
        }
    }

    Err(ExecutionError::mismatched_types(trace))
}

pub fn check_obj_kind<'a>(
    expected: &Object<'a>,
    actual: &Object<'a>,
    trace: &AST
) -> RuntimeResult<'a, ()> {
    match expected {
        Object::Hashable(HashableObject::Integer(_)) => {
            check_kind(Kind::Integer, actual, trace)
        }

        Object::Hashable(HashableObject::Float(_)) => {
            check_kind(Kind::Float, actual, trace)
        }

        Object::Hashable(HashableObject::Boolean(_)) => {
            check_kind(Kind::Boolean, actual, trace)
        }

        Object::Hashable(HashableObject::String(_)) => {
            check_kind(Kind::String, actual, trace)
        }

        Object::NonHashable(NonHashableObject::List(_)) => {
            check_kind(Kind::List, actual, trace)
        }

        Object::NonHashable(NonHashableObject::Dictionary(_)) => {
            check_kind(Kind::Dictionary, actual, trace)
        }

        Object::Void => {
            Err(ExecutionError::mismatched_types(trace))
        }

        Object::Any(_) => {
            Ok(())
        }
    }
}