//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("SzolariumInit.res");
USEFORM("SzolariumInitMain.cpp", FormMain);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->Title = "Szolárium Vezérlõ Inicializálás";
       Application->CreateForm(__classid(TFormMain), &FormMain);
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
