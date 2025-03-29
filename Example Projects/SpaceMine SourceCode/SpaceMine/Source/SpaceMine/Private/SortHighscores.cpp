// Fill out your copyright notice in the Description page of Project Settings.


#include "SortHighscores.h"

void USortHighscores::Sort(TArray<FHighscoreItem>& _highscoresToSort , TArray<FHighscoreItem>& _sortedHighscores)
{
	for(int i = 0; i < _highscoresToSort.Num(); ++i)
	{
		for (int j = _highscoresToSort.Num()-1; j>i; --j)
		{
			if(_highscoresToSort[j].Score < _highscoresToSort[j - 1].Score)
			{
				FHighscoreItem temp = _highscoresToSort[j];

				_highscoresToSort[j] = _highscoresToSort[j - 1];

				_highscoresToSort[j - 1] = temp;
			}
		}
	}

	_sortedHighscores = _highscoresToSort;
}
