#pragma once

#include <iostream>
#include <stdio.h>
#include <tuple>
#include <vector>
#include <algorithm>
#include <ctime>

#include "Node.h"
#include "Edge.h"

class Maze
{
private:
	int width;
	int height;
	vector<Node*> unions;
	vector<Edge*> edges;

public:
	Maze(int width = 3, int height = 3)
	{
		srand(time(NULL));

		this->width = width;
		this->height = height;

		if (IsValid())
		{
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					unions.push_back(new Node());
					unions.at(unions.size() - 1)->SetCoords(x * 2 + 1, y * 2 + 1);
				}
			}

			{
				/*for (int x = 0; x < width; x++)
				{
					for (int y = 0; y < height; y++)
						printf("%d,%d\t", get<0>(unions.at(x * width + y)->GetCoords()), get<1>(unions.at(x * width + y)->GetCoords()));
					printf("\n");
				}*/

				//printf("\n\n");
			}

			for (int x = 0; x < width; x++)
				for (int y = 0; y < height - 1; y++)
					edges.push_back(new Edge(unions.at(x * width + y), unions.at(x * width + y + 1)));

			for (int x = 0; x < width - 1; x++)
				for (int y = 0; y < height; y++)
					edges.push_back(new Edge(unions.at(x * width + y), unions.at((x + 1) * width + y)));

			random_shuffle(edges.begin(), edges.end());

			{
				/*for (int x = 0; x < width; x++)
				{
					for (int y = 0; y < height; y++)
						printf("%d,%d\t", get<0>(unions.at(x * width + y)->GetCoords()), get<1>(unions.at(x * width + y)->GetCoords()));
					printf("\n");
				}*/

				/*for (int i = 0; i < edges.size(); i++)
				{
					printf("%d,%d -> %d,%d\n", get<0>(edges[i]->GetFirst()->GetCoords()), get<1>(edges[i]->GetFirst()->GetCoords()), get<0>(edges[i]->GetSecond()->GetCoords()), get<1>(edges[i]->GetSecond()->GetCoords()));
				}*/

				//printf("\n\n");

				/*for (int x = 0; x < width; x++)
				{
					for (int y = 0; y < height; y++)
					{
						if (!unions.at(x * width + y)->FindUnion(unions.at(x * width + y + 1)))
						{
							unions.at(x * width + y)->MergeUnions(unions.at(x * width + y + 1));
							//printf("%d\t%d,%d : %d,%d\n", x * width + y, get<0>(unions.at(x * width + y)->GetCoords()), get<1>(unions.at(x * width + y)->GetCoords()), get<0>(unions.at(x * width + y + 1)->GetCoords()), get<1>(unions.at(x * width + y + 1)->GetCoords()));
						}

						if (!unions.at(x * width + y)->FindUnion(unions.at((x + 1) * width + y)))
						{

						}
					}
				}*/

				/*Node* walker;// = unions.at(0 * width + height - 1);
				//printf("%d\t%d,%d", 0 * width + height - 1, get<0>(unions.at(0 * width + height - 1)->GetCoords()), get<1>(unions.at(0 * width + height - 1)->GetCoords()));

				for (int x = 0; x < width; x++)
				{
					walker = unions.at(x * width + height - 1);
					//printf("\n%d\t%d,%d, %s\n", x * width + height - 1, get<0>(unions.at(x * width + height - 1)->GetCoords()), get<1>(unions.at(x * width + height - 1)->GetCoords()), walker->HasParent() ? "true" : "false");

					while (walker != NULL)
					{
						printf("%d,%d -> ", get<0>(walker->GetCoords()), get<1>(walker->GetCoords()));
						walker = walker->GetParent();
					}

					printf("\n");
				}*/
			}

			for (int i = 0; i < edges.size(); i++)
			{
				if (!edges.at(i)->GetFirst()->FindUnion(edges.at(i)->GetSecond()))
					edges.at(i)->GetFirst()->MergeUnions(edges.at(i)->GetSecond());
				else
					edges.at(i)->SetDestroy(true);
			}


			for (int i = 0; i < edges.size(); i++)
			{
				if (edges.at(i)->GetDestroy())
				{
					edges.erase(edges.begin() + i);
					i--;
				}
			}

			Node* walker;

			{
				/*for (int x = 0; x < width; x++)
				{
					for (int y = 0; y < height; y++)
					{
						walker = unions.at(y * height + x);

						while (walker != NULL)
						{
							printf("%d,%d -> ", get<0>(walker->GetCoords()), get<1>(walker->GetCoords()));
							walker = walker->GetParent();
						}
						printf("\n");
					}
					printf("\n");
				}*/

				//printf("\n");

			/*for (int i = 0; i < edges.size(); i++)
			{
				printf("%d,%d -> %d,%d\n", get<0>(edges.at(i)->GetFirst()->GetCoords()), get<1>(edges.at(i)->GetFirst()->GetCoords()), get<0>(edges.at(i)->GetSecond()->GetCoords()), get<1>(edges.at(i)->GetSecond()->GetCoords()));
			}*/

				//printf("\n");
			}
		}
		else
		{
			printf("Invalid data:");
			
			if (width < 2)
				printf("\nWidth smaller than minimal value");
			if (height < 2)
				printf("\nHeight smaller than minimal value");
		}
	}

	int myrandom(int i) { return rand() % i; }

	void Print()
	{
		bool ctrl = false;
		int j = 0;
		for (int y = 0; y < height * 2 + 1; y++)
		{
			for (int x = 0; x < width * 2 + 1; x++)
			{
				if ((x == 0 && y == 1) || (x == width * 2 && y == height * 2 - 1))
					printf(" ");
				else if (x % 2 != 0 && y % 2 != 0)
					printf(" ");
				else if (x - 1 >= 0 && x + 1 < width * 2 + 1 && y - 1 >= 0 && y + 1 < height * 2 + 1)
				{
					ctrl = false;
					for (int i = 0; i < edges.size(); i++)
					{
						if ((x - 1 == get<0>(edges.at(i)->GetFirst()->GetCoords()) && y == get<1>(edges.at(i)->GetFirst()->GetCoords())) && (x + 1 == get<0>(edges.at(i)->GetSecond()->GetCoords()) && y == get<1>(edges.at(i)->GetSecond()->GetCoords())) ||
							(x - 1 == get<0>(edges.at(i)->GetSecond()->GetCoords()) && y == get<1>(edges.at(i)->GetSecond()->GetCoords())) && (x + 1 == get<0>(edges.at(i)->GetFirst()->GetCoords()) && y == get<1>(edges.at(i)->GetFirst()->GetCoords())))
						{
							printf(" ");
							ctrl = true;
							break;
						}
						else if ((x == get<0>(edges.at(i)->GetFirst()->GetCoords()) && y - 1 == get<1>(edges.at(i)->GetFirst()->GetCoords())) && (x == get<0>(edges.at(i)->GetSecond()->GetCoords()) && y + 1 == get<1>(edges.at(i)->GetSecond()->GetCoords())) ||
								 (x == get<0>(edges.at(i)->GetSecond()->GetCoords()) && y - 1 == get<1>(edges.at(i)->GetSecond()->GetCoords())) && (x == get<0>(edges.at(i)->GetFirst()->GetCoords()) && y + 1 == get<1>(edges.at(i)->GetFirst()->GetCoords())))
						{
							printf(" ");
							ctrl = true;
							break;
						}
					}
					if (!ctrl)
						printf("#");
				}
				else
					printf("#");
			}

			printf("\n");
		}
	}

private:
	bool IsValid()
	{
		if (width >= 2 && height >= 2)
			return true;
		return false;
	}
};