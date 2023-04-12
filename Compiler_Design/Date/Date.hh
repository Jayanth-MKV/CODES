#ifndef Date_H_
#define Date_H_

class Date{
       
       short int day;
       short int month;
       short int year;
    public:
    	Date();
    	Date(short int, short int, short int);
    	Date(const Date &); //copy constructor        
        Date operator+(int num);
        Date operator-(int num);
        int operator-(Date);        
        bool isItValid();
        void print();
};
#endif