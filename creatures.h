#include <iostream>

class Creature;
class Creature_Society;

struct info{
	Creature* creat;
	Creature_Society* soc;
	unsigned int index;
};

class Creature{
	protected:
	char* name;
	unsigned int L;
	info* place;

	public:
	virtual bool beat(){
		if (is_a_zombie() == false){
			L--;
			return false;
		}
		return true;
	}
	virtual bool bless(){
		if (is_a_zombie() == false){
			L++;
			return false;
		}
		return true;
	}
	bool is_a_zombie(void) const{
		if (L == 0){
			return true;
		}
		return false;
	}
	virtual bool is_a_good() const = 0;
	Creature(const char*, int, info*);
	~Creature();
	Creature(const Creature&);
	
};

class Good_Creature : public Creature{
	unsigned int good_thrsh;
	
	bool is_a_good() const{
		return true;
	}

	public:
	bool bless();
	bool beat();
	Good_Creature(const char*, int, info*, int);
	// Helping constructor for cloning.
	Good_Creature(const Creature&, int);
};

class Bad_Creature : public Creature{
	unsigned int bad_thrsh;

	bool is_a_good() const{
		return false;
	}

	public:
	bool bless();
	bool beat();
	Bad_Creature(const char*, int, info*, int);
	// Helping constructor for cloning.
	Bad_Creature(const Creature&, int);
};

class Creature_Society{
	unsigned int N;
	unsigned int good_thrsh;
	unsigned int bad_thrsh;
	unsigned int good_creatures;
	unsigned int zombies;
	info** society;

	void clone_next(int);
	void clone_zombies(int);

	public:
	Creature_Society(int, int, int, int);
	~Creature_Society();
	
	void bless(int);
	void beat(int);
	
	unsigned int no_of_good() const;
	unsigned int no_of_zombies() const;
};