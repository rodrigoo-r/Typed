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

pub type List<'a> = Vec<Object<'a>>;
pub type Dictionary<'a> = 
    HashMap<HashableObject<'a>, Object<'a>>;

pub type Float = OrderedFloat<f32>;

#[derive(PartialEq, Eq, Debug)]
pub enum StringKind<'a> {
    Static(&'a str),
    Dynamic(String)
}

#[derive(Debug)]
pub enum HashableObject<'a> {
    String(StringKind<'a>),
    Integer(isize),
    Boolean(bool),
    Float(Float),
}

#[derive(Debug)]
pub enum NonHashableObject<'a> {
    Dictionary(Dictionary<'a>),
    List(List<'a>)
}

#[derive(Debug)]
pub enum Object<'a> {
    Hashable(HashableObject<'a>),
    NonHashable(NonHashableObject<'a>),
    Void,
    Any(Rc<RefCell<Object<'a>>>)
}