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
mod runtime;

use std::env;
use pest::Parser;
use crate::core::*;
use crate::core::backend::execute;
use support::failable::{catch_non_traceable, catch_pest};
use crate::runtime::get_global_package;
use crate::support::failable::catch;

fn main() {
    // Get the path from argv[0]
    let args: Vec<String> = env::args().collect();
    let path = &args[1];

    let contents = support::file::read(path.as_str());
    let contents = catch_non_traceable(&contents);
    let tree = core::frontend::parser::Parser::parse(
        frontend::parser::Rule::Program,
        contents.as_ref()
    );

    let tree = catch_pest(&tree);
    let ast = frontend::parser::convert(tree.clone());
    let global_package = get_global_package();

    let file = middle_end::pre_walker::convert(ast, &global_package);
    let file = catch(&file);

    catch(&execute(file));
}
