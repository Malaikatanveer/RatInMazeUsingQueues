#include<SFML/Graphics.hpp>
#include<iostream>
#include"Windows.h"
#include <ctime>
#include <stdlib.h>     
#include <time.h> 
using namespace std;
sf::RenderWindow window(sf::VideoMode(850, 850), "Lee's Algorithm");
template <typename t>
class queue
{

	class node
	{
		int x;   //x and y are coordinates
		int y;
		int dis;
		node* next;
		friend class queue<t>;
	public:
		node()
		{
			dis = -1;
			x = -1;
			y = -1;
			next = nullptr;
		}

		node(int xco, int yco, int d, node* n)
		{
			dis = d;
			x = xco;
			y = yco;
			next = n;
		}

		node(const node& obj)
		{
			this->dis = obj.dis;
			this->x = obj.x;
			this->y = obj.y;
			this->next = obj.next;
		}
		~node()
		{
			next = nullptr;
		}
	};
	node* front;
	node* rear;
public:
	queue();
	~queue();
	queue(node*, node*);
	queue(const queue&);
	bool isempty();
	bool isfull();
	void enqueue(int, int, int);
	void dequeue(int&, int&, int&);
	int* frontdata();
	int* reardata();
};


template<typename t>
queue<t>::queue()
{
	front = nullptr;
	rear = nullptr;
}


template<typename t>
queue<t>::queue(node* f, node* r)
{
	front = f;
	rear = r;
}


template<typename t>
queue<t>::queue(const queue& obj)
{
	this->front = obj.front;
	this->rear = obj.rear;
}



template<typename t>
queue<t>::~queue()
{
	rear = nullptr;
	front = nullptr;
}



template<typename t>
bool queue<t>::isempty()
{
	if (front == nullptr && rear == nullptr)
	{
		return true;
	}
	else
		return false;
}

template<typename t>
bool queue<t>::isfull()
{
	return false;
}


template<typename t>
void queue<t>::enqueue(int xco, int yco, int distance)
{
	if (isempty())
	{
		node* temp = new node;
		temp->x = xco;
		temp->y = yco;
		temp->dis = distance;
		temp->next = nullptr;
		front = temp;
		rear = temp;
	}
	else if (!isempty())
	{
		node* temp = new node;
		temp->x = xco;
		temp->y = yco;
		temp->dis = distance;
		temp->next = nullptr;
		rear->next = temp;
		rear = rear->next;
	}
}


template<typename t>
void queue<t>::dequeue(int& xco, int& yco, int& d)
{
	d = front->dis;
	xco = front->x;
	yco = front->y;
	node* temp = front;
	front = front->next;
	if (front == nullptr)
	{
		rear = nullptr;     //meaning the queue has become empty
	}
	delete temp;
	temp = nullptr;
}


template<typename t>
int* queue<t>::frontdata()
{
	int* arr = new int[3];
	arr[0] = this->front->x;
	arr[1] = this->front->y;
	arr[2] = this->front->dis;
	return arr;

}


template<typename t>
int* queue<t>::reardata()
{
	int* arr = new int[3];
	arr[0] = this->rear->x;
	arr[1] = this->rear->y;
	arr[2] = this->rear->dis;
	return arr;

}


void printarr(int** arr, int r, int c)
{
	for (int i = 0;i < r;i++)
	{
		for (int j = 0;j < c;j++)
		{
			if (arr[i][j] >= 0)
				cout << " ";
			cout << arr[i][j] << "  ";
		}
		cout << endl;
	}
}



void gamelogic()
{
	int r = 0, c = 0;
	int entry1 = -1, entry2 = -1;
	int destination1 = -1, destination2 = -1;
	cout << "enter rows for the maze: ";
	cin >> r;
	cout << endl;
	cout << "enter columns for the maze: ";
	cin >> c;
	cout << endl;
	int** arr = new int* [r];
	for (int i = 0;i < r;i++)
	{
		arr[i] = new int[c];
	}
	for (int i = 0;i < r;i++)
	{
		for (int j = 0;j < c;j++)
		{
			arr[i][j] = -1;
		}
	}
	cout << "enter row index for entry point: ";
	cin >> entry1;
	cout << endl;
	cout << "enter column index for entry point: ";
	cin >> entry2;
	cout << endl;

	cout << "enter row index for destination point: ";
	cin >> destination1;
	cout << endl;
	cout << "enter column index for destination point: ";
	cin >> destination2;
	cout << endl;
	////////////////////////////////////////////////////////////////////////////


	if (r <= 8)
	{
		sf::RectangleShape line1(sf::Vector2f(r * 100, 1));   //Vector2f(500, 1)
		line1.rotate(90);
		sf::RectangleShape line2(sf::Vector2f(c * 100, 1));

		for (int i = 1; i < (c * 100) + 100; i = i + 100)                  //(int i = 1; i < 600; i = i + 100)
		{

			line1.setPosition(i, 0);                               //line1.setPosition(i, 0);

			window.draw(line1);

		}
		for (int i = 0; i < (r * 100) + 100; i = i + 100)                    //(int i = 0; i < 600; i = i + 100)
		{

			line2.setPosition(0, i);                               //line2.setPosition(0, i);
			window.draw(line2);
		}


	}


	/////////////////////////////////////////////////////////////////////////////
	int num;
	srand(time(0));
	int totalblocks = r * c;
	num = 0 + rand() % (totalblocks - 0 + 1);   //num is total hurdles
	num = num / 2;     //to keep the number low as compared to the free blocks
	cout << "number of hurdles: " << num << endl;
	int* numx = new int[num];
	int* numy = new int[num];
	for (int i = 0;i < num;i++)
	{
		numx[i] = 0 + rand() % (((r - 1) + 1) - 0);    //numx conatins all x coordinates for random placement
	}
	for (int i = 0;i < num;i++)
	{
		numy[i] = 0 + rand() % (((c - 1) + 1) - 0);    //numy conatins all y coordinates for random placement
	}
	for (int i = 0;i < num;i++)
	{
		arr[numx[i]][numy[i]] = -2;     //-1 shows hurdles
		cout << "hurdle at: " << numx[i] << "  " << numy[i] << endl;

	}
	int counter = 0;
	arr[entry1][entry2] = counter;         //0 shows entry point
	arr[destination1][destination2] = -3;
	int temp1 = entry1;
	int temp2 = entry2;
	printarr(arr, r, c);
	cout << endl;

	//////////////////////////////////////////////////////////////////////


	sf::Texture green;               //starting position, ending point
	if (!(green.loadFromFile("green.png")))
	{
		cout << "error\n";
	}
	sf::Sprite g;
	g.setTexture(green);
	if (r <= 8)
	{
		g.setScale(sf::Vector2f(0.16, 0.16));
		for (int i = 0;i < r;i++)
		{
			for (int j = 0;j < c;j++)
			{
				if (arr[i][j] == 0)
				{
					g.setPosition(j * 100, i * 100);
					window.draw(g);
				}
			}
		}
	}


	if (r <= 8)    //destination
	{
		g.setScale(sf::Vector2f(0.16, 0.16));
		for (int i = 0;i < r;i++)
		{
			for (int j = 0;j < c;j++)
			{
				if (arr[i][j] == -3)
				{
					g.setPosition(j * 100, i * 100);
					window.draw(g);
				}
			}
		}
	}

	sf::Texture hurdles;
	if (!(hurdles.loadFromFile("blue.png")))
	{
		cout << "error\n";
	}
	for (int i = 0;i < r;i++)
	{
		for (int j = 0;j < c;j++)
		{
			if (arr[i][j] == -2)
			{

				sf::Sprite b;
				b.setTexture(hurdles);
				b.setScale(sf::Vector2f(0.08, 0.08));
				if (i == 0 && j == 0)
					b.setPosition(i, j);
				else if (i == 0 && j != 0)
					b.setPosition(j * 100, i);
				else if (i != 0 && j == 0)
					b.setPosition(j, i * 100);
				else
					b.setPosition(j * 100, i * 100);


				window.draw(b);

			}
		}
	}





	//////////////////////////////////////////////////////////////////////

	// 0 shows entry point, -1 shows all possible places that can be visited and -2 shows hurdles, -3 shows destination , -5 shows the final backtracked path
	queue<char>q;
	q.enqueue(temp1, temp2, counter);
	bool flagfordes = false;
	int tempxco = 0, tempyco = 0, tempdis = 0;
	int lastdis = 0;



	sf::Texture finalpath;
	if (!(finalpath.loadFromFile("yellow.png")))
	{
		cout << "error\n";
	}


	while (!flagfordes && !q.isempty())
	{
		sf::Sprite y;
		y.setTexture(finalpath);
		y.setScale(sf::Vector2f(0.08, 0.08));

		q.dequeue(tempxco, tempyco, tempdis);
		if (lastdis < tempdis)
		{
			counter++;
		}
		lastdis = tempdis;

		if (tempxco + 1 < r && arr[tempxco + 1][tempyco] != -2 && (arr[tempxco + 1][tempyco] == -1 || arr[tempxco + 1][tempyco] == -3))
		{
			arr[tempxco + 1][tempyco] = counter + 1;
			q.enqueue(tempxco + 1, tempyco, counter + 1);
		/*	y.setPosition( tempyco, (tempxco + 1) * 100);
			window.display();
			window.draw(y);
			window.display();
			Sleep(1000);*/


		}
		if (tempxco - 1 >= 0 && arr[tempxco - 1][tempyco] != -2 && (arr[tempxco - 1][tempyco] == -1 || arr[tempxco - 1][tempyco] == -3))
		{
			arr[tempxco - 1][tempyco] = counter + 1;
			q.enqueue(tempxco - 1, tempyco, counter + 1);
			/*y.setPosition( tempyco, (tempxco - 1) * 100);
			window.display();
			window.draw(y);
			window.display();
			Sleep(1000);*/

		}
		if (tempyco + 1 < c && arr[tempxco][tempyco + 1] != -2 && (arr[tempxco][tempyco + 1] == -1 || arr[tempxco][tempyco + 1] == -3))
		{
			arr[tempxco][tempyco + 1] = counter + 1;
			q.enqueue(tempxco, tempyco + 1, counter + 1);
			/*y.setPosition((tempyco + 1) * 100,tempxco );
			window.display();
			window.draw(y);
			window.display();
			Sleep(1000);*/

		}
		if (tempyco - 1 >= 0 && arr[tempxco][tempyco - 1] != -2 && (arr[tempxco][tempyco - 1] == -1 || arr[tempxco][tempyco - 1] == -3))
		{
			arr[tempxco][tempyco - 1] = counter + 1;
			q.enqueue(tempxco, tempyco - 1, counter + 1);
		/*	y.setPosition((tempyco - 1) * 100,tempxco);
			window.display();
			window.draw(y);
			window.display();
			Sleep(1000);*/

		}
		

		if (tempxco + 1 < r)
		{
			if (tempxco + 1 == destination1 && tempyco == destination2)
			{

				flagfordes = true;
			}
		}

		if (tempxco - 1 >= 0)
		{
			if (tempxco - 1 == destination1 && tempyco == destination2)
			{

				flagfordes = true;

			}
		}

		if (tempyco + 1 < c)
		{
			if (tempxco == destination1 && tempyco + 1 == destination2)
			{

				flagfordes = true;

			}
		}

		if (tempyco - 1 >= 0)
		{
			if (tempxco == destination1 && tempyco - 1 == destination2)
			{

				flagfordes = true;

			}
		}
	}
	printarr(arr, r, c);
	cout << endl << endl << endl;
	int tempcounter = counter;



	if (flagfordes == true)
	{
		if (arr[tempxco][tempyco] == tempcounter)
		{
			arr[tempxco][tempyco] = -5;
			arr[destination1][destination2] = -5;
			for (int i = tempxco, j = tempyco;tempcounter > 0;)
			{
				if (i + 1 < r && arr[i + 1][j] == tempcounter - 1)
				{
					arr[i + 1][j] = -5;
					cout << endl;
					printarr(arr, r, c);
					i++;
				}
				else if (i - 1 >= 0 && arr[i - 1][j] == tempcounter - 1)
				{
					arr[i - 1][j] = -5;
					cout << endl;
					printarr(arr, r, c);
					i--;
				}
				else if (j + 1 < c && arr[i][j + 1] == tempcounter - 1)
				{
					arr[i][j + 1] = -5;
					cout << endl;
					printarr(arr, r, c);
					j++;
				}
				else if (j - 1 >= 0 && arr[i][j - 1] == tempcounter - 1)
				{

					arr[i][j - 1] = -5;
					cout << endl;
					printarr(arr, r, c);
					j--;
				}
				tempcounter--;
			}
		}
	}
	for (int i = 0;i < r;i++)
	{
		for (int j = 0;j < c;j++)
		{
			if (arr[i][j] == -5)
			{
				sf::Sprite y;
				y.setTexture(finalpath);
				y.setScale(sf::Vector2f(0.08, 0.08));
				if (i == 0 && j == 0)
				{
					y.setPosition(i, j);
					//window.display();
					window.draw(y);
				/*	window.display();
					Sleep(1000);*/

				}
				else if (i == 0 && j != 0)
				{
					y.setPosition(j * 100, i);
					//window.display();
					window.draw(y);
					/*window.display();
					Sleep(1000);*/

				}
				else if (i != 0 && j == 0)
				{
					y.setPosition(j, i * 100);
					//window.display();
					window.draw(y);
				/*	window.display();
					Sleep(1000);*/

				}
				else
				{
					y.setPosition(j * 100, i * 100);
					//window.display();
					window.draw(y);
					/*window.display();
					Sleep(1000);*/


				}
			}
			
		}
	}
	cout << endl;
	printarr(arr, r, c);
	window.display();
}




int main()
{
	gamelogic();
	system("pause");
	return 0;
}