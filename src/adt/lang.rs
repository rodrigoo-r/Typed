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
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{List, Object};
use crate::core::frontend::parser::Rule;

pub type BaseChildAST<'a> = RefCell<AST<'a>>;
pub type ChildAST<'a> = Rc<BaseChildAST<'a>>;
pub type ASTChildren<'a> = RefCell<Vec<ChildAST<'a>>>;

pub type RuntimeArguments<'a> = List<'a>;
pub type NativeProcedure<'a> =
    fn(RuntimeArguments<'a>, &AST<'a>) -> ExecutionResult<'a>;

#[derive(Debug, Clone)]
pub struct AST<'a> {
    pub rule: Rule,
    pub children: ASTChildren<'a>,
    pub value: Option<&'a str>,
    pub line: usize,
    pub column: usize
}

#[derive(Debug, Clone)]
pub enum Kind {
    String,
    Integer,
    Boolean,
    Float,
    Dictionary,
    List
}

#[derive(Debug, Clone)]
pub struct Argument<'a> {
    pub name: &'a str,
    pub kind: Kind
}

#[derive(Debug, Clone)]
pub struct Procedure<'a> {
    pub arguments: Vec<Argument<'a>>,
    pub body: Option<ChildAST<'a>>,
    pub variadic: bool,
    pub native: Option<NativeProcedure<'a>>
}

#[derive(Debug)]
pub struct File<'a> {
    pub imports: Vec<String>,
    pub procedures: HashMap<&'a str, Procedure<'a>>
}