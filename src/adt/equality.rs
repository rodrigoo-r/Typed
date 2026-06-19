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
use std::ops::Deref;
use crate::adt::runtime::{HashableObject, NonHashableObject, Object};

fn compare_hashable_obj(lhs: &HashableObject, rhs: &HashableObject) -> bool {
    match (lhs, rhs) {
        (HashableObject::String(a), HashableObject::String(b)) => a == b,
        (HashableObject::Integer(a), HashableObject::Integer(b)) => a == b,
        (HashableObject::Boolean(a), HashableObject::Boolean(b)) => a == b,
        (HashableObject::Float(a), HashableObject::Float(b)) => a == b,

        _ => false
    }
}

fn compare_obj(lhs: &Object, rhs: &Object) -> bool {
    if matches!(lhs, Object::NonHashable(_)) ||
        matches!(rhs, Object::NonHashable(_))
    {
        return false;
    }

    match (lhs, rhs) {
        (Object::Hashable(a), Object::Hashable(b)) => compare_hashable_obj(a, b),

        _ => false
    }
}

impl<'a> PartialEq for HashableObject<'a> {
    fn eq(&self, other: &Self) -> bool {
        if self.variant_id() == other.variant_id() {
            return false;
        }

        compare_hashable_obj(self, other)
    }
}

impl<'a> PartialEq for NonHashableObject<'a> {
    fn eq(&self, other: &Self) -> bool {
        false
    }
}

impl<'a> PartialEq for Object<'a> {
    fn eq(&self, other: &Self) -> bool {
        if
            let Object::Any(a) = self &&
            let Object::Any(b) = other
        {
            let lhs = a.borrow();
            let lhs = lhs.deref();

            let rhs = b.borrow();
            let rhs = rhs.deref();

            compare_obj(lhs, rhs)
        }
        else if let Object::Any(a) = self {
            let obj = a.borrow();
            let obj = obj.deref();

            compare_obj(obj, other)
        }
        else if let Object::Any(a) = other {
            let obj = a.borrow();
            let obj = obj.deref();

            compare_obj(self, obj)
        }
        else {
            compare_obj(self, other)
        }

    }
}

impl<'a> Eq for HashableObject<'a> {}
impl<'a> Eq for NonHashableObject<'a> {}
impl<'a> Eq for Object<'a> {}
