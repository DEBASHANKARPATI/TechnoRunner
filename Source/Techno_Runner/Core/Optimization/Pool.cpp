// Fill out your copyright notice in the Description page of Project Settings.
#include "Pool.h"
#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>

APool::APool()
{

}

void APool::InstantiateSplineMeshes( USplineComponent*const TargetSpline, UMaterial*const InMaterial, UStaticMesh*const InStaticMesh, int SegmentLength)
{
	//Optimize this using Object pool
	int TotalSplineLength = TargetSpline->GetSplineLength();
	float CurrentDistance = 0;
	while (CurrentDistance < TotalSplineLength)
	{
		USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
		SplineMesh->RegisterComponent();
		SplineMesh->SetMobility(EComponentMobility::Movable);

		FVector StartPosition = TargetSpline->GetLocationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::Local);
		FVector EndPosition = TargetSpline->GetLocationAtDistanceAlongSpline(CurrentDistance + SegmentLength, ESplineCoordinateSpace::Local);

		FVector StartTangent = TargetSpline->GetTangentAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::Local);
		FVector EndTangent = TargetSpline->GetTangentAtDistanceAlongSpline(CurrentDistance + SegmentLength, ESplineCoordinateSpace::Local);


		FVector2D StartScale = FVector2D(TargetSpline->GetScaleAtDistanceAlongSpline(CurrentDistance));
		FVector2D EndScale = FVector2D(TargetSpline->GetScaleAtDistanceAlongSpline(CurrentDistance + SegmentLength));

		SplineMesh->SetStartAndEnd(StartPosition, StartTangent, EndPosition, EndTangent);
		SplineMesh->SetStartScale(StartScale);
		SplineMesh->SetEndScale(EndScale);

		SplineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		SplineMesh->SetStaticMesh(InStaticMesh);
		SplineMesh->SetMaterial(0, InMaterial);
		SplineMesh->SetForwardAxis(ESplineMeshAxis::X);
		SplineMesh->AttachToComponent(TargetSpline , FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		SplineMeshComponentList.Add(SplineMesh);

		CurrentDistance += SegmentLength;
	}
}

TArray<USplineMeshComponent*> APool::GetSplineMeshPool()
{
	return SplineMeshComponentList;
}

void APool::RecycleSplineMeshes(USplineComponent* const TargetSpline , float PreviousSplineLength , UMaterial* const InMaterial, UStaticMesh* const InStaticMesh , int SegmentLength , int Count)
{ 
	float CurrentDistance = TargetSpline->GetSplineLength() - SegmentLength;

	if (USplineMeshComponent* const SplineMesh = SplineMeshComponentList[0])
	{
		FVector StartPosition = TargetSpline->GetLocationAtDistanceAlongSpline( CurrentDistance, ESplineCoordinateSpace::Local);
		FVector EndPosition = TargetSpline->GetLocationAtDistanceAlongSpline( CurrentDistance + SegmentLength, ESplineCoordinateSpace::Local);

		FVector StartTangent = TargetSpline->GetTangentAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::Local);
		FVector EndTangent = TargetSpline->GetTangentAtDistanceAlongSpline(CurrentDistance + SegmentLength , ESplineCoordinateSpace::Local);


		FVector2D StartScale = FVector2D(TargetSpline->GetScaleAtDistanceAlongSpline(CurrentDistance));
		FVector2D EndScale = FVector2D(TargetSpline->GetScaleAtDistanceAlongSpline(CurrentDistance + SegmentLength));

		SplineMesh->SetStartAndEnd(StartPosition, StartTangent, EndPosition, EndTangent);
		SplineMesh->SetStartScale(StartScale);
		SplineMesh->SetEndScale(EndScale);
		SplineMesh->SetStaticMesh(InStaticMesh);
		SplineMesh->SetMaterial(0, InMaterial);
		SplineMeshComponentList.Add(SplineMesh);
	}
	SplineMeshComponentList.RemoveAt(0);
}