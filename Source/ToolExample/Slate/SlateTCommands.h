#pragma once

class FSlateTCommands: public TCommands<FSlateTCommands>
{
	
public:
	FSlateTCommands();
	virtual void RegisterCommands() override;

	static TSharedRef<FUICommandList> CommandList;

	//Example
	TSharedPtr<FUICommandInfo> OpenWindow;
	TWeakPtr<SWindow> OpenWindowPtr;
	void OpenWindow_Function();

	//Materilas
	TSharedPtr<FUICommandInfo> ReplaceMaterials;
	TWeakPtr<SWindow> ReplaceMaterialsWindowPtr;
	void OpenReplacerWindow_Function();


	TWeakObjectPtr<UMaterialInterface> SelectedMaterial;
	TWeakObjectPtr<UStaticMesh> SelectedMesh;
	void OnMeshSelected(const FAssetData& AssetData);
	void OnMaterialSelected(const FAssetData& AssetData);

	FReply OnReplaceMaterialsClicked();

	//Date View
	TSharedPtr<FUICommandInfo> OpenMeshReplaceMaterialsWindow;
	TWeakPtr<SWindow> OpenMeshReplaceMaterialsWindowPtr;
	void OpenMeshReplaceMaterialsWindow_Function();
};
