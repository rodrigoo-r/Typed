-- // Imports // --
with Ada.Text_IO;
with Ada.Command_Line;
with Ada.Exceptions;
with Cli.Exceptions;

package body Cli.Core is   
   function Process return String is
      use Ada.Text_IO;
      use Ada.Command_Line;
      use Ada.Exceptions;
      use Cli.Exceptions;
   begin
      -- Make sure we have at least one argument
      if Argument_Count < 1 then
         raise No_Arguments;
      end if;

      return Argument (1);
   end Process;

end Cli.Core;