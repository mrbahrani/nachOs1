#ifndef TIMETABLE_H
#define TIMETABLE_H


// include here necessary headers
struct Record
{
	void* func;
	int exectTime;
};
class Timetable{
public:
	Timetable();
	~Timetable();
	int find(void *);
	int getAverage();
	void update(void *,int);

private:
	unsigned int numberOfRecords;
	 Record record[100];
};

#endif
