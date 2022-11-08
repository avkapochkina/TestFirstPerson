// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAmmoWidget.h"

void UBaseAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
//	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

//	TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("TextBlock")); // The second parameter is the name and is optional.
//	TextBlock->OnClicked.AddDynamic(this, &BaseAmmoWidget::OnButtonClicked); // Example click binding.
//	RootWidget->AddChild(ExampleButton);
	// Bind delegates here.
}

void UBaseAmmoWidget::UpdateWidget(const int8& Clips, const int8& Bullets)
{
	if(GetVisibility() == ESlateVisibility::Visible)
	{
		TextBlock->SetText(FText::FromString("Clips: %d\nBullets: %d" + Clips + Bullets));
	}
}