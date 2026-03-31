with Ada.Command_Line; use Ada.Command_Line;
with Ada.Exceptions; use Ada.Exceptions;
with Ada.Text_IO; use Ada.Text_IO;
with Terminal; use Terminal;
with Ansi; use Ansi;
with Wide_Terminal;

package body Cli.Reporter is

   procedure Report (Ex : Exception_Occurrence) is
      Identity : constant String := Exception_Name    (Ex);
      Msg      : constant String := Exception_Message (Ex);
   begin
      Write_Line_Colored (Bright_Red & Bold, "error: " & Identity);
      Wide_Terminal.Write_Colored (Bright_Black, "  ↳ ");
      Put_Line (Msg);
      Put_Line (""); -- Empty line for spacing
      Write_Line_Colored (Bright_Black, "(!) Exiting with failure status");
      Set_Exit_Status (1);
   end Report;

end Cli.Reporter;