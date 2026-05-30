#include<iostream>
using namespace std;

class roaddept
{
private:
    string condition, status;
    int maxw;
public:
    void setdata(){
        cout<<"Enter the road condition(good,bad,damaged):\n";//here we take in the values that are necessary for the parameters mentioned
        cin>>condition;//takes in the condition of the road(good,bad,maintenance)
        cout<<"Enter the road status(open,closed,under construction):\n";
        cin>>status;//takes in wether road is open or closed 
        cout<<"Enter the max weight road can bear(in kgs):\n";//takes in the maximum weight the road can handle 
        cin>>maxw;
    }
    friend class decision;
};

class trafmngmt{
private:
    int nov,time,avgsp,ql;
public:
    void setdata(){
        cout<<"Enter the no of vehicles:\n";
        cin>>nov;//nov is no. of vehicles
        cout<<"Enter the time(in 24hrs format (only hrs needed)):\n";
        cin>>time;//takes in time 
        cout<<"Enter the avg speed(in km/hr format):\n";
        cin>>avgsp;//takes in avg speed of vehicles 
        cout<<"Enter the queue length:\n";
        cin>>ql;//queue lenght of vehicles 
    }
    friend class decision;
};

class decision{
public:
    string decs(roaddept r, trafmngmt t){

        bool peak = (t.time >= 8 && t.time <= 10) || 
                    (t.time >= 17 && t.time <= 19);//this logic gives true or false according to the time 

        bool midnight = (t.time >= 1 && t.time <= 4);//this logic gives true or false according to nigh time 

        if(r.condition == "good" && r.status == "open" &&
           t.nov == 50 && t.ql == 10)
        {
            return "GREEN SIGNAL";
        }

        else if(peak && t.avgsp >= 25 && r.status == "open" && t.ql == 20)//this cases have been inspired by real world scenarios 
        {
            return "GREEN SIGNAL";
        }

        else if(t.nov > 100 && t.avgsp < 10 && t.ql > 30)
        {
            return "RED SIGNAL";
        }

        else if(r.status == "damaged")
        {
            return "RED SIGNAL";
        }

        else if(r.condition == "good" && t.avgsp > 80)
        {
            return "RED SIGNAL";
        }

        else if(peak && t.nov > 120 && t.avgsp < 15 && t.ql > 40)
        {
            return "RED SIGNAL";
        }

        else if(r.condition == "bad" && t.avgsp > 40)
        {
            return "RED SIGNAL";
        }

        else if(t.nov * 1000 > r.maxw)
        {
            return "RED SIGNAL";
        }

        else if(r.status == "maintenance" && t.nov < 15 && t.avgsp < 20)
        {
            return "GREEN SIGNAL";
        }

        else if(t.nov <= 50 && t.ql > 30 && t.avgsp < 15)
        {
            return "GREEN SIGNAL";
        }

        else if(midnight && t.nov < 5)
        {
            return "GREEN SIGNAL";
        }

        else if(r.condition == "good" && r.status == "open" &&
                t.avgsp >= 30 && t.ql <= 20 && t.nov <= 60)
        {
            return "GREEN SIGNAL";
        }

        else if(peak && r.maxw < 15000)
        {
            return "RED SIGNAL";
        }

        else if(midnight && t.avgsp > 70)
        {
            return "RED SIGNAL";
        }

        else if(r.condition == "average" && t.nov > 90)
        {
            return "RED SIGNAL";
        }

        else if(t.time == 7 && t.nov > 80)
        {
            return "GREEN SIGNAL";
        }

        else if(t.avgsp < 5 && t.ql > 60)
        {
            return "RED SIGNAL";
        }

        else//this mathematical formula is derived from internet,it calculates the score based on no of vehicles(nov),queue length (qv) ,and average speed
        {
            float score = 0;
            score += 0.4 * t.nov;
            score += 0.3 * t.ql;
            score += 0.3 * (100 - t.avgsp);

            if(score > 70)
                return "RED SIGNAL";//it says rea signal is score is greater than 70
            else
                return "GREEN SIGNAL";
        }
    }
};

int main(){
    /* this code is made for enterprise level and not for average daily consumer ,its intended to be used by clients who understand in and out of traffic management ,the program feeds in 
    live data and releases its opininon if the traffic is to be allowed to move forward or not */
	roaddept g;
    trafmngmt h;
    decision d;

    g.setdata();
    h.setdata();

    cout<<"The decision is "<<d.decs(g,h)<<endl;
}
