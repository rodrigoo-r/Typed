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
use std::cell::RefCell;
use std::collections::HashMap;
use std::rc::Rc;
use ordered_float::OrderedFloat;

#[derive(PartialEq, Eq)]
pub enum StringKind<'a> {
    Static(&'a str),
    Dynamic(String)
}

pub enum HashableObject<'a> {
    String(StringKind<'a>),
    Integer(isize),
    Boolean(bool),
    Float(OrderedFloat<f32>),
}

pub enum NonHashableObject<'a> {
    Dictionary(HashMap<HashableObject<'a>, Object<'a>>),
    List(Vec<HashableObject<'a>>)
}

pub enum Object<'a> {
    Hashable(HashableObject<'a>),
    NonHashable(NonHashableObject<'a>),
    Void,
    Any(Rc<RefCell<Object<'a>>>)
}