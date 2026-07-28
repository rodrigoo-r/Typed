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

use std::io::Read;
use pest::Parser;
use crate::adt::lang::AST;
use crate::core::frontend::parser::old::OldGrammarParser;
use crate::core::frontend::parser::{old, standard};
use crate::core::frontend::parser::standard::StandardParser;
use crate::support::failable::catch_pest;

pub fn read(path: &str) -> Result<String, std::io::Error> {
    let mut file = std::fs::File::open(path)?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;

    Ok(contents)
}

pub fn parse<'ast>(
    contents: &'ast String,
    syntax: &'ast str
) -> AST<'ast> {
    let ast;

    if syntax == "standard" {
        let tree = StandardParser::parse(
            standard::Rule::Program,
            contents.as_ref()
        );

        let tree = catch_pest(&tree).clone();
        ast = standard::grammar::convert(tree);
    } else if syntax == "old" {
        let tree = OldGrammarParser::parse(
            old::Rule::Program,
            contents.as_ref()
        );

        let tree = catch_pest(&tree).clone();
        ast = old::grammar::convert(tree);
    } else {
        panic!("Unknown syntax: {}", syntax);
    }
    
    ast
}