#include "EditorToolsModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FEditorToolsModule, EditorToolsModule);

void FEditorToolsModule::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("EditorToolsModule has started!"));
}

void FEditorToolsModule::ShutdownModule()
{
    UE_LOG(LogTemp, Log, TEXT("EditorToolsModule has shut down!"));
}
