#include "HintDetailsCustomization.h"
#include "ExplosiveUnboxing/Hint.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Input/SButton.h"

TSharedRef<IDetailCustomization> FHintDetailsCustomization::MakeInstance()
{
    return MakeShareable(new FHintDetailsCustomization());
}

void FHintDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Hints");

    TArray<TSharedPtr<FText>> ConditionOptions;
    TSharedPtr<SListView<TSharedPtr<ULogic>>> LogicListView;

    for (int32 i = 0; i < (int32)Conditions::MAX; ++i)
    {
        ConditionOptions.Add(MakeShared<FText>(FText::FromString(UEnum::GetValueAsString((Conditions)i))));
    }

    Category.AddCustomRow(FText::FromString("Add Logic"))
        .ValueContent()
        [
            SNew(SButton)
                .Text(FText::FromString("Add Logic"))
                .OnClicked_Lambda([this]()
                    {
                        if (HintAsset.IsValid())
                        {
                            // To do
                            
                        }
                        return FReply::Handled();
                    })
        ];
}
