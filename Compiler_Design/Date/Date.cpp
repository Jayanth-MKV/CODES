#include "Date.hh"
#include<iostream>
using namespace std;

Date::Date(){}
Date::Date(short int d, short int m, short int y){
         day=d;
         month=m;
         year=y;
}

Date::Date(const Date &d){
        day=d.day;
        month=d.month;
        year=d.year;
}        

Date Date::operator+(int obj){
        Date res;
		
		res.year=year+((obj/360));	
		obj=obj%360;
		res.month=month+(obj/30);
		if(res.month>12){
		res.year+=1;	
		res.month=(res.month)%12;	
		}
		obj=obj%30;	
	
		int sum=day+obj;
		
		if(sum<=30){
		
		res.day=sum;
		
		}
		else{
		res.day=(sum%30);
		if(res.month!=12){
		res.month+=1;
		}
		else{
		res.month=1;
		res.year+=1;	
		}
		
		}

         return res;
}
/*
Date Date::operator-(int obj){
        Date res;
		
		res.year=year-((obj/360));	
		obj=obj%360;
		res.month=month-(obj/30);
		if(res.month<1)
		{
		res.month=12-(res.month);	
		res.year-=1;
		}
		obj=obj%30;
		int diff=day-obj;
		
		if(diff>0){
		
		res.day=diff;
		
		}
		else{
		res.day=30+(diff);
		if(res.month!=1){
		res.month-=1;
		}
		else{
		res.month=12;
		res.year-=1;	
		}
		}

         return res;
}
*/

Date Date::operator - (int obj) {
         Date res;

                res.year=year-((obj/360));      
                obj=obj%360;
                res.month=month-(obj/30);
                if(res.month<1)
                {
                res.month=12-(res.month);       
                res.year-=1;
                }
                obj=obj%30;
                int diff=day-obj;

                if(diff>0){

                res.day=diff;

                }
                else{
                res.day=30+(diff);
                if(res.month!=1){
                res.month-=1;
                }
                else{
                res.month=12;
                res.year-=1;    
                }
                }

         return res;
    }



int Date::operator-(Date obj){
        Date res;
        
        long long days1=(year)*360+(month)*30+(day);
        long long days2=(obj.year)*360+(obj.month)*30+(obj.day);
		
		int cnt=0;
		
		cnt=max(days1,days2)-min(days1,days2);
		
         return cnt;
}        

bool Date::isItValid(){
        return true;
}

void Date::print(){
       cout<<day<<"/"<<month<<"/"<<year<<endl;
}


/*
  DE '-'  NUMBER      {        $$ = new ExprValue();
                                    cout<<"Success"<<endl;
                                    $$->v.date= new Date(*($1->v.date)-($3));
                                    $$->vt=DATE_VALUE;
                           }
*/
