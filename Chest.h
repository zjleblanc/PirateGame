#ifndef CHEST_H
#define CHEST_H

using namespace std;

class Chest : public Entity {
public:
	Chest(int, int);
	int getx();
	int gety();
	int isopen();
	void openChest();

private:
	int x, y;
	int open;
};
#endif
