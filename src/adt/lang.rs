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
use crate::core::frontend::parser::Rule;

#[derive(Debug, Clone)]
pub struct AST<'a> {
    pub rule: Rule,
    pub children: RefCell<Vec<Rc<RefCell<AST<'a>>>>>,
    pub value: Option<&'a str>,
    pub line: usize,
    pub column: usize
}

#[derive(Debug)]
pub enum Kind {
    String,
    Integer,
    Boolean,
    Float,
    Dictionary,
    List
}

#[derive(Debug)]
pub struct Argument<'a> {
    pub name: &'a str,
    pub kind: Kind
}

#[derive(Debug)]
pub struct Procedure<'a> {
    pub arguments: Vec<Argument<'a>>,
    pub body: Rc<RefCell<AST<'a>>>
}

#[derive(Debug)]
pub struct File<'a> {
    pub imports: Vec<String>,
    pub procedures: HashMap<&'a str, Procedure<'a>>
}