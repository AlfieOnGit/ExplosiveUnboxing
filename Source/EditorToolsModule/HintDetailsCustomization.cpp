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
    UEnum* Enum = StaticEnum<Conditions>();
    if (Enum)
    {
        for (int32 i = 0; i < (int32)Conditions::MAX; ++i)
        {
            if (i == (int32)Conditions::MAX)
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
                UStatement* MyStatement = NewObject<UStatement>();
                //MyStatement->probability = 50;
               // MyStatement->statement = Statements::EQUAL;

                MyObject->logic.Add(MyStatement);
            }
            return FReply::Handled();
        };

    Category.AddCustomRow(LOCTEXT("MyButtonRowFilterString", "Search Filter Keywords"))
        .WholeRowContent()
        [
            SNew(SButton)
                .Text(LOCTEXT("RegenerateBtnText", "Regenerate List"))
                .OnClicked_Lambda(OnRegenerate)
        ];

    /*Category.AddCustomRow(FText::FromString("Select Condition"))
        .ValueContent()
        [
            SNew(SComboBox<TSharedPtr<FText>>)
                .OptionsSource(&ConditionOptions)
                .OnSelectionChanged_Lambda([this](TSharedPtr<FText> NewSelection, ESelectInfo::Type SelectInfo)
                    {
                        if (NewSelection.IsValid())
                        {
                            // To do
                        }
                    })
                .Content()
                [
                    SNew(STextBlock)
                        .Text(FText::FromString("Select a condition"))
                ]
        ];*/
}
