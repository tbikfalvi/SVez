//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("SolariumSetup.res");
USEFORM("DialogSelectDir.cpp", FormDialogSelectDir);
USEFORM("SetupMain.cpp", FormInstallMain);
USEUNIT("ClassSerialComm.cpp");
USEUNIT("ClassHardware.cpp");
USEUNIT("ClassGeneral.cpp");
USEUNIT("SerialClass.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->CreateForm(__classid(TFormInstallMain), &FormInstallMain);
       Application->CreateForm(__classid(TFormDialogSelectDir), &FormDialogSelectDir);
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
