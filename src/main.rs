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

mod core;
mod support;
mod adt;

use std::env;
use pest::Parser;
use crate::core::*;
use crate::core::backend::execute;

fn main() {
    // Get the path from argv[0]
    let args: Vec<String> = env::args().collect();
    let path = &args[1];

    let contents = support::file::read(path.as_str());
    if contents.is_err() {
        panic!("could not read file")
    }

    let contents = contents.unwrap();
    let tree = core::frontend::parser::Parser::parse(
        frontend::parser::Rule::Program,
        contents.as_str()
    );

    let raw_tree = tree.unwrap();
    let ast = frontend::parser::convert(raw_tree);
    let file = middle_end::pre_walker::convert(ast);

    execute(file);
}
