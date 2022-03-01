#include "cards.h"

#include <iostream>

using namespace std;

bool bang::use()
{
	if ((game->rtnPlayers()[game->now_playing]).bangcount <= 0)
	{
		cout << "you can't use bang anymore\n";
		return false;
	}
	else
	{
		game->rtnPlayers()[game->now_playing].bangcount--;

		cout << "choose target\n";
		int target;
		for (auto it = game->rtnPlayers().begin(); it != game->rtnPlayers().end(); it++)
		{
			cout << target << " : " << *it << endl;
			target++;
		}
		while (true)
		{
			cin >> target;
			cin.get();
			if (target >= game->rtnNplayer())
			{
				cout << "wrong target. choose again.\n";
				continue;
			}
			else
			{
				if (game->rtnPlayers()[target].haveCard("missed"))
				{
					game->rtnPlayers()[target].usingCard();
					//cout << "use missed? y or n\n";
					//char choice;
					//cin >> choice;
					//cin.get();
					//if (choice == 'n')
					//{
					//	game->rtnPlayers()[target].setLife(-1);
					//	return true;
					//}
					//else
					//{
					//	game->rtnPlayers()[target].u
					//	return true;
					//}
				}
				else
				{
					game->rtnPlayers()[target].setLife(-1);
					return true;
				}
			}
		}

	}
}