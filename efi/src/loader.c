#include "loader.h"
#include <efi.h>
#include <efilib.h>

// EFI Image Entry Point
EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    (void)ImageHandle;
            
    // Set text to yellow fg/ green bg
    SystemTable->ConOut->SetAttribute(
        SystemTable->ConOut, 
        EFI_TEXT_ATTR(EFI_YELLOW,EFI_GREEN)
    ); 

    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);

    SystemTable->ConOut->OutputString(SystemTable->ConOut, u"hi chat\r\n\r\n");
    
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 
            EFI_TEXT_ATTR(EFI_RED,EFI_BLACK));

    SystemTable->ConOut->OutputString(SystemTable->ConOut, 
            u"press any key to shutdown..."); 

            // wait until key is pressed
    EFI_INPUT_KEY key;
    while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) != EFI_SUCCESS);
    
    // shutdown, no return
    SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);

    // should never get here
    return EFI_SUCCESS;
}
