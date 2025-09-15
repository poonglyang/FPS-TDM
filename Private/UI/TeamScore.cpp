// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TeamScore.h"

FString UTeamScore::GetTeamNameText(int index)
{
	FString temp = "";

	for (int i = 0; i < index; i++) {
		temp += TeamName[i];
	}
	return temp;
}

int UTeamScore::GetTeamNameLength()
{
	
	return TeamName.Len();
}


