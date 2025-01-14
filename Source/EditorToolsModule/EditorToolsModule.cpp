#include "EditorToolsModule.h"
#include "Modules/ModuleManager.h"

#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "HintDetailsCustomization.h"
#include "UObject/WeakObjectPtr.h"
#include "ExplosiveUnboxing/Hint.h"



IMPLEMENT_MODULE(FEditorToolsModule, EditorToolsModule);

void FEditorToolsModule::StartupModule()
{
    FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyEditorModule.RegisterCustomClassLayout(UHint::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FHintDetailsCustomization::MakeInstance));
    UE_LOG(LogTemp, Log, TEXT("EditorToolsModule has started!"));
}

void FEditorToolsModule::ShutdownModule()
{
    UE_LOG(LogTemp, Log, TEXT("EditorToolsModule has shut down!"));
}
