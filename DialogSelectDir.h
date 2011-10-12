//---------------------------------------------------------------------------

#ifndef DialogSelectDirH
#define DialogSelectDirH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TFormDialogSelectDir : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TDriveComboBox *DriveComboBox;
   TDirectoryListBox *DirectoryListBox;
   TBitBtn *BitBtnOk;
   TBitBtn *BitBtnCancel;
   TGroupBox *GroupBox2;
   TLabel *LabelDir;
private:	// User declarations
public:		// User declarations
   __fastcall TFormDialogSelectDir(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDialogSelectDir *FormDialogSelectDir;
//---------------------------------------------------------------------------
#endif
