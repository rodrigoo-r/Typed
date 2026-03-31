with Ada.Exceptions; use Ada.Exceptions;
with Ada.Text_IO; use Ada.Text_IO;

package body Cli.Reporter is

   procedure Report (Ex : Exception_Occurrence) is
      Identity : constant String := Exception_Name    (Ex);
      Msg      : constant String := Exception_Message (Ex);
   begin
      Put_Line ("error: " & Identity);
      Put_Line (""); -- Empty line for spacing
      Put_Line (Msg);
   end Report;

end Cli.Reporter;