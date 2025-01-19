#include "HintDetailsCustomization.h"
#include "ExplosiveUnboxing/Hint.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "EditorToolsModule"

TSharedRef<IDetailCustomization> FHintDetailsCustomization::MakeInstance()
{
    return MakeShareable(new FHintDetailsCustomization());
}

void FHintDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Hints");
    TSharedRef<IPropertyHandle> Prop = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UHint, logic));
    //DetailBuilder.HideProperty(Prop);

    TArray< TWeakObjectPtr<UObject>> Objects;
    DetailBuilder.GetObjectsBeingCustomized(Objects);    
    
    if (Objects.Num() != 1){ return; }
    TWeakObjectPtr<UHint> MyObject = Cast<UHint>(Objects[0].Get());

    auto OnGetPropVisibility = [MyObject] { return MyObject.IsValid() ? EVisibility::Visible : EVisibility::Collapsed;};
    auto PropVisibilityAttr = TAttribute< EVisibility >::Create(TAttribute<EVisibility>::FGetter::CreateLambda(OnGetPropVisibility));


    TArray<TSharedPtr<FText>> ConditionOptions;
    UEnum* Enum = StaticEnum<LogicTypes>();
    if (Enum)
    {
        for (int32 i = 0; i < (int32)LogicTypes::MAX; ++i)
        {
            if (i == (int32)LogicTypes::MAX)
                continue;

            ConditionOptions.Add(MakeShared<FText>(Enum->GetDisplayNameTextByIndex(i)));
        }
    }

    Category.AddCustomRow(LOCTEXT("MyWarningRowFilterString", "Search Filter Keywords"))
        .Visibility(PropVisibilityAttr)
        .WholeRowContent()
        [
            SNew(STextBlock)
                .Text(LOCTEXT("MyWarningTest", "BaseString should not be empty!"))
        ];

    auto OnRegenerate = [MyObject]
        {
            if (MyObject.IsValid())
            {
                MyObject->logic.Add(AllLogic::Equal);
                MyObject->logic.Add(AllLogic::CaseNumber);
                MyObject->logic.Add(AllLogic::Danger);
            }
            return FReply::Handled();
        };

    Category.AddCustomRow(LOCTEXT("MyButtonRowFilterString", "Search Filter Keywords"))
        .WholeRowContent()
        [
            SNew(SHorizontalBox) + SHorizontalBox::Slot()
            [
                SNew(SComboBox<TSharedPtr<FText>>)
                    .OptionsSource(&ConditionOptions)
                    .OnSelectionChanged_Lambda([MyObject](TSharedPtr<FText> NewSelection, ESelectInfo::Type SelectInfo)
                        {
                            if (MyObject.IsValid())
                            {
                                // Create new Logic data here from enum
                                /*ULogicData* MyLogic = NewObject<ULogicData>();
                                if (!MyLogic)
                                {
                                    UE_LOG(LogTemp, Error, TEXT("Failed to create ULogicData!"));
                                    return;
                                }
                                MyLogic->LogicStatement = LogicNamespace::Truthful;
                                MyObject->logic.Add(MyLogic);*/
                            }
                        })
                    .Content()
                    [
                        SNew(STextBlock).Text_Lambda([ConditionOptions]() { return *ConditionOptions[0]; })

                    ]
            ]
            + SHorizontalBox::Slot().Padding(5, 0)
            [
            SNew(SButton)
                .Text(LOCTEXT("RegenerateBtnText", "Regenerate List"))
                .OnClicked_Lambda(OnRegenerate)
            ]
        ];
}
