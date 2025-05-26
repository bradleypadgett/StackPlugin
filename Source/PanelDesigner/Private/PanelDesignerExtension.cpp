#include "PanelDesignerExtension.h"
#include "Graph/PanelDesignerGraphSchema.h"
#include "PanelDesignerEditor.h"
#include "Graph/PanelDesignerGraph.h"
#include "EdGraph/EdGraph.h"



// Creates and serializes PanelDesignerGraph into owning blueprint if it doesn't have one
TObjectPtr<UPanelDesignerGraph> UPanelDesignerExtension::EnsurePanelDesignerGraph()
{


    UBlueprint* Blueprint = GetTypedOuter<UBlueprint>();

    if (PanelDesignerGraph) 
    {
        if (PanelDesignerGraph->Schema == UPanelDesignerGraphSchema::StaticClass())
        {
            PanelDesignerGraph->Schema = UPanelDesignerGraphSchema::StaticClass();
            return PanelDesignerGraph;

        }
        UE_LOG(LogTemp, Error, TEXT("Designer graph has incorrect schema! Removing it to avoid crash."));
        Blueprint->FunctionGraphs.Remove(PanelDesignerGraph);
    }


    //loops through incase it wasn't set properly but still exists in the bp
 //   for (UEdGraph* Graph : Blueprint->FunctionGraphs)
//    {
 //       if (UPanelDesignerGraph* Found = Cast<UPanelDesignerGraph>(Graph))
 //       {
//            PanelDesignerGraph = Found;
 //           PanelDesignerGraph->Schema = UPanelDesignerGraphSchema::StaticClass();
 //           return PanelDesignerGraph;
 //       }
 //   }

    UE_LOG(LogTemp, Warning, TEXT("Creating Graph inside extension!"));
    PanelDesignerGraph = NewObject<UPanelDesignerGraph>(Blueprint, TEXT("Designer"), RF_Transactional);
    PanelDesignerGraph->Schema = UPanelDesignerGraphSchema::StaticClass();

    return PanelDesignerGraph;
}

void UPanelDesignerExtension::AttachPanelDesignerGraph(UBlueprint* Blueprint)
{
    if (bNewExtension)
    {
        UE_LOG(LogTemp, Warning, TEXT("adding in new graph woo !"));
        //Blueprint->UbergraphPages.GetData
        //Blueprint->UbergraphPages.Add(PanelDesignerGraph);
        //Blueprint->LastEditedDocuments.Add(FEditedDocumentInfo(PanelDesignerGraph));
        bNewExtension = false;
    }
}