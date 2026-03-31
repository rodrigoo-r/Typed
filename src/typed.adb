with Cli.Core;
with Cli.Reporter;
with Ada.Text_IO;
with Ada.Strings.Unbounded;

procedure Typed is
   use Ada.Text_IO;
   use Ada.Strings.Unbounded;

   Path : Unbounded_String;
begin
   Path := To_Unbounded_String (Cli.Core.Process);
   Put_Line ("Path: " & To_String (Path));

exception
   when E : others =>
      Cli.Reporter.Report (E);
end Typed;