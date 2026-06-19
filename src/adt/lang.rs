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

pub enum Kind {
    String,
    Integer,
    Float,
    Dictionary,
    List
}

pub struct Argument<'a> {
    pub name: &'a str,
    pub kind: Kind
}

pub struct Procedure<'a> {
    pub arguments: Vec<Argument<'a>>,
    pub body: AST<'a>
}

pub struct File<'a> {
    imports: Vec<String>,
    procedures: HashMap<String, Procedure<'a>>
}