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

pub mod core;
pub mod support;
pub mod adt;
pub mod runtime;
pub mod cli;

use clap::Parser;
use crate::cli::{Cli, Commands};
use crate::cli::command::run;

fn main() {
    let cli = Cli::parse();

    match cli.command {
        Commands::Run { file } => {
            run::handle(&file);
        }
    }
}