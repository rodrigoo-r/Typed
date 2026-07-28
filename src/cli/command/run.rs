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
use pest::Parser;
use crate::cli::RunCommand;
use crate::core::middle_end;
use crate::core::backend::execute;
use crate::core::frontend::parser::old::OldGrammarParser;
use crate::core::frontend::parser::{old, standard};
use crate::core::frontend::parser::standard::StandardParser;
use crate::runtime::get_global_package;
use crate::support;
use crate::support::failable::{catch, catch_non_traceable, catch_pest};

pub fn handle(cmd: &RunCommand) {
    let contents = support::file::read(cmd.file.as_str());
    let contents = catch_non_traceable(&contents);
    let syntax = &cmd.syntax;

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

    let global_package = get_global_package();

    let file = middle_end::pre_walker::convert(ast, &global_package);
    let file = catch(&file);

    catch(&execute(file));
}