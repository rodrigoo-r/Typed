with Ada.Exceptions; use Ada.Exceptions;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Cli.Exceptions; use Cli.Exceptions;

package body Cli.Reporter is

   procedure Report (Ex : Exception_Occurrence) is
      Msg : Unbounded_String := To_Unbounded_String (Exception_Message (Ex));
   begin
      Put ("error: ");

      if Exception_Identity (Ex) = No_Arguments'Identity then
         Msg := To_Unbounded_String ("No arguments provided.");
      end if;

      Put_Line (To_String (Msg));
   end Report;

end Cli.Reporter;