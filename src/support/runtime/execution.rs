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

use crate::adt::runtime::Object;

macro_rules! execute_or_return {
    ($expr:expr, $trace:expr) => {{
        let res = $expr;

        if res != Object::Void {
            return Ok(res);
        }
    }}
}