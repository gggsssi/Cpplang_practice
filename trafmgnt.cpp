#include<iostream>
using namespace std;

class roaddept
{
	private:
		string condition,status;
		int maxw;
	public:
		void setdata(){
			cout<<"Enter the condition:\n";
			cin>>condition;
		    cout<<"Enter the status:\n";
		    cin>>status;
		    cout<<"Enter the max weight road can bear:\n";
		    cin>>maxw;
		};
	friend class decision;
		};

class trafmngmt{
	private:
		int nov,time,avgsp,ql;
	public:
		void setdata(){
			cout<<"Enter the no of vehicles:\n";
			cin>>nov;
			cout<<"Enter the time(in 24hrs format):\n";
			cin>>time;
			cout<<"Enter the avg speed(in km/hr format):\n";
			cin>>avgsp;
			cout<<"Enter the queue length:\n";
			cin>>ql;
			};
			
		friend class decision;
};

class decision(){
	public:
		string decs(roaddept r,trafmgmt t){
			bool peak = (t.time >= 8 && t.time <= 10) || 
                    (t.time >= 17 && t.time <= 19);

            bool midnight = (t.time >= 1 && t.time <= 4);
			if(condition = "good",status = "open",nov = 50,avgsp = ,ql = 10)
			else if(((time >= 8 && time <= 10) || (time >= 17 && time <= 19)),avgsp >= 25,ql = 20,status = "open",ql = 20)
             else if(nov > 100,avgsp < 10,ql > 30)
              else if(r.status == "damaged")
               {
                  cout << "RED SIGNAL\n";
               }
			  else if (r.condition == "good" && t.avgsp > 80)
              {
                cout << "RED SIGNAL\n";
                }
               else if (t.nov > 100 && t.avgsp < 10 && t.ql > 30)
        {
            cout << "RED SIGNAL\n";
        }
		 else if (peak && t.nov > 120 && t.avgsp < 15 && t.ql > 40)
        {
            cout << "RED SIGNAL\n";
        }
        else if (peak && t.nov > 120 && t.avgsp < 15 && t.ql > 40)
        {
            cout << "RED SIGNAL\n";
        }
        else if (r.condition == "bad" && t.avgsp > 40)
        {
            cout << "RED SIGNAL\n";
        }
        else if (t.nov * 1000 > r.maxw)   // assuming avg vehicle weight = 1000kg
        {
            cout << "RED SIGNAL\n";
        }
        else if (r.status == "maintenance" && t.nov < 15 && t.avgsp < 20)
        {
            cout << "GREEN SIGNAL\n";
        }
        else if (t.nov <= 50 && t.ql > 30 && t.avgsp < 15)
        {
            cout << "GREEN SIGNAL\n";
        }
        else if (midnight && t.nov < 5)
        {
            cout << "GREEN SIGNAL\n";
        }
        else if (r.condition == "good" && r.status == "open" &&
                 t.avgsp >= 30 && t.ql <= 20 && t.nov <= 60)
        {
            cout << "GREEN SIGNAL\n";
        }
        else if (peak && r.maxw < 15000)
{
    cout << "RED SIGNAL\n";
}
else if (midnight && t.avgsp > 70)
{
    cout << "RED SIGNAL\n";
}
else if (r.condition == "good" && r.status == "open" &&
         t.nov >= 70 && t.nov <= 100 &&
         t.avgsp >= 25)
{
    cout << "GREEN SIGNAL\n";
}
else if (t.ql > 50 && t.avgsp >= 20)
{
    cout << "GREEN SIGNAL\n";  // Clear backlog
}
else if (r.condition == "average" && t.nov > 90)
{
    cout << "RED SIGNAL\n";
}
else if (t.time == 7 && t.nov > 80)
{
    cout << "GREEN SIGNAL\n";
}
else if (t.avgsp < 5 && t.ql > 60)
{
    cout << "RED SIGNAL\n";
}
else{
float calculateCongestionScore(trafmgmt t)
{
    float score = 0;

    score += 0.4 * t.nov;      // vehicle density weight
    score += 0.3 * t.ql;       // queue impact
    score += 0.3 * (100 - t.avgsp); // lower speed increases score

    return score;
}
void decide(roaddept r, trafmgmt t)
{
    float cs = calculateCongestionScore(t);

    if (r.status == "damaged")
    {
        cout << "RED SIGNAL\n";
    }
    else if (cs > 70)
    {
        cout << "RED SIGNAL\n";
    }
    else
    {
        cout << "GREEN SIGNAL\n";
    }
}
};
		
	};

int main(){
	roaddept g;
	trafmngmt h;
	decision d;
	g.setdata();
	h.setdata();
	cout<<"the decision is "<<d.decs(g,h)<<end1;
}




