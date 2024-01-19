//#include<iostream>
//#include<string>
//#include<fstream>
//#include <cassert>
//using namespace std;
//template <class v>
//struct HashItem
//{
//	int key;
//	v value;
//	short status;
//	HashItem(int key=0,v value=v(), short status = 0)
//	{
//		this->key = key;
//		this->value = value;
//		this->status = status;
//	}
//};
//template <class v>
//class HashMap
//{
//private:
//	int capacity;
//	virtual int getNextCandidateIndex(int key, int&i)
//	{
//		return (key+i)%capacity  ;
//	}
//	HashItem<v>* hashArray;
//	int currentElements;
//public:
//	HashMap()
//	{
//		currentElements = 0;
//		this->capacity = 10;
//		hashArray = new HashItem<v>[10]();
//	}
//	HashMap(int const capacity)
//	{
//		currentElements = 0;
//		this->capacity = capacity;
//		hashArray = new HashItem<v>[capacity];
//	}
//	void insert(int const key, v const value)
//	{
//		++currentElements;
//		HashItem<v>newitem(key, value);
//		if ((hashArray[key % capacity].status == 0) || (hashArray[key % capacity].status ==1))
//		{
//			hashArray[key % capacity] = newitem;
//			newitem.status = 2;
//			return;
//		}
//		int i = 1;
//		int newind = getNextCandidateIndex(key, i);
//		while (hashArray[newind].status==2)
//		{
//			i++;
//			newind = getNextCandidateIndex(key, i);
//		}
//		hashArray[newind] = newitem;
//
//	}
//	void doublecapacity(){
//		HashItem<v>* temp = new HashItem<v>[capacity];
//		for (int i = 0;i < capacity;i++) {
//			temp[i] = hashArray[i];
//		}
//		delete hashArray;
//		capacity = capacity * 2;
//		hashArray = new HashItem<v>[capacity];
//		int index = 0;
//		for (int i = 0;i < capacity;i++) {
//			index = temp[i].key % capacity;
//			if (hashArray[index] != nullptr) {
//				hashArray[index] = temp[i];
//			}
//			else{
//				int j = 1;
//				index = getNextCandidateIndex(temp[i].key, j);
//				while (hashArray[index].status==2) {
//					++j;
//					index = getNextCandidateIndex(temp[i].key, j);
//				}
//				hashArray[index] = temp[i];
//			}
//		}
//	}
//	bool deleteKey(int const key) {
//		int index = key % capacity;
//		if (hashArray[index].key == key) {
//			hashArray[index].status = 2;
//			--currentElements;
//			return 1;
//		}
//		int i = 1;
//		index = getNextCandidateIndex(key, i);
//		while (hashArray[index].key == 0) {
//			i++;
//			index = getNextCandidateIndex(key, i);
//		}
//		if (hashArray[index].key == key) {
//			hashArray[index].status = 2;
//			--currentElements;
//			return 1;
//		}
//		return 0;
//	}
//	v* get(int const key) {
//		int index =key % capacity;
//		if (hashArray[index].key == key && hashArray[index].status!=2) {
//			return &hashArray[index].value;
//		}
//		int i = 1;
//		index = getNextCandidateIndex(key, i);
//		while (hashArray[index].key== 0) {
//			i++;
//			index = getNextCandidateIndex(key, i);
//		}
//		if (hashArray[index].key == key && hashArray[index].status != 2)
//			return &hashArray[index].value;
//			return nullptr;
//	}
//	int getCapacity(){
//		return this->capacity;
//	}
//	~HashMap()
//	{
//		delete[] hashArray;
//	}
//};
//template<class v>
//class QhashMap:public HashMap<v>
//{	
//	virtual int getNextCandidateIndex(int key, int& i)
//	{
//		return (key + i*i) % HashMap<v>::getCapacity();
//	}
//public:
//	QhashMap() :HashMap<v>() {};
//	QhashMap(int cap) :HashMap<v>(cap) {};
//
//};
//template <class v>
//class DhashMap : public HashMap<v>
//{
//	virtual int getNextCandidateIndex(int key,int &i) {
//		int f = key %HashMap<v>::getCapacity();
//		int s = 7 - (key % 7);
//		return((f + i * s) % HashMap<v>::getCapacity());
//	}
//public:
//	DhashMap() :HashMap<v>() {};
//	DhashMap(int cap) :HashMap<v>(cap) {};
//	
//};
//
//void populateHash(string filename, HashMap<string>*hash) {
//	ifstream file(filename);
//	if (file.is_open()) {
//		int id;
//		string name;
//
//		while (file >> id >> name) {
//			hash->insert(id, name);
//		}
//
//		file.close();
//	}
//	else {
//		cerr << "Error opening file: " << filename << endl;
//	}
//}
//int main()
//{
//	HashMap<string>* map;
//	map = new HashMap<string>;
//	populateHash("students.txt", map);
//	if (map->get(9) != nullptr)
//	{
//		cout << *map->get(9)<<"\n";
//	}
//	map->deleteKey(9);
//	assert(map->get(9) == nullptr);
//	delete map;
//
//	map = new QhashMap<string>;
//	populateHash("students.txt", map);
//	if (map->get(5) != nullptr)
//	{
//		cout << *map->get(5)<<"\n";
//	}
//	map->deleteKey(98);
//	assert(map->get(98) == nullptr);
//	delete map;
//	map = new DhashMap<string>;
//
//	populateHash("students.txt", map);
//	if (map->get(1) != nullptr)
//	{
//		cout << *map->get(1)<<"\n";
//	}
//	map->deleteKey(101);
//	assert(map->get(101) == nullptr);
//	delete map;
//	return 0;
//
//
//}
//
