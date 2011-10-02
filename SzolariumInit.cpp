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
       Application->Title = "Szol�rium Vez�rl� Inicializ�l�s";
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
