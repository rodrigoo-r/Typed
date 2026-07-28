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
use crate::cli::FormatCommand;
use crate::core::formatter::format;
use crate::support::failable::{catch_non_traceable};
use crate::support::file;

pub fn handle(cmd: &FormatCommand) {
    let contents = file::read(cmd.file.as_str());
    let contents = catch_non_traceable(&contents);
    let ast = file::parse(&contents, &cmd.input_syntax);

    let fmt = format(&ast, &cmd.output_syntax);
    let res = file::write(cmd.output.as_str(), &fmt);

    if res.is_err() {
        panic!("{}", res.err().unwrap());
    }
}