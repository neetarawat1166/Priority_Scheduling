#include<iostream>
#include<Math.h>
using namespace std;
void getData();
void sortData();
void calcualte();

int bt[20];
int p[20];
int wt[20];
int tat[20];
int at[20];
int rt[20];
int pr[20];
	
int i,j,n,pos,temp,wasted=0;
float avg_wt,avg_tat,avg_rt,T,U,total_bt=0,total_wt=0,total_tat=0,total_rt=0;
		

void getData()
{
		cout<<"\n\n\nThis Program Is Written And Executed By Neeta Rawat\n";
		cout<<"\nAlgorithm Used: PRIORITY SCHEDULING\n\n";
		cout<<"\nEnter Total Number Of Processes: ";
	    cin>>n;

	   cout<<"\n\nEnter Burst Time, Arrival Time And Priority: \n";
		for(i=0;i<n;i++)
		{
		    cout<<"\nP["<<(i+1)<<"]";
            cout<<"\nBurst Time: ";	
            cin>>bt[i];
           cout<<"Arrival Time: ";	
            cin>>at[i];	
            cout<<"Priority: ";	
            cin>>pr[i];				
            p[i] = i+1;		
			total_bt+=bt[i];
		}
}

void sortData()
	{
		//sorting burst time, priority, arrival time and process number in ascending order
		//using selection sort
		
		cout<<"\n\nGANTT CHART:\n\n";
		for(i=0;i<n;i++)
		{
			pos=i;
            for(j=i+1;j<n;j++)
            {
                if(pr[j]<pr[pos] && pr[j]<at[pos])
                  pos=j;
            }
		    cout<<"\tP"<<p[pos];
			
			temp=pr[i];
			pr[i]=pr[pos];
			pr[pos]=temp;
 
            temp=bt[i];
            bt[i]=bt[pos];
            bt[pos]=temp;
			
			temp=at[i];
            at[i]=at[pos];
            at[pos]=temp;
 
            temp=p[i];
            p[i]=p[pos];
            p[pos]=temp;
		}
	}
	
	void calculate()
	{
		//calculate waiting time
		//Service time means amount of time after which a process can start execution.
		
		int service_time[n];
		service_time[0] = at[0];
		wt[0] = 0;
		
		// calculating waiting time
		
		for (int i=1;i<n;i++)
		{
			service_time[i] = service_time[i-1] + bt[i-1];
			wt[i] = service_time[i] - at[i];
			
			// If waiting time is negative it means it is already in the ready queue
			// before CPU becomes idle so its waiting time is 0
			
			if (wt[i] < 0) 
			{
				wasted = abs(wt[i]);
				wt[i] = 0;
			}
			
			total_wt+=wt[i];
			
			//Add wasted time
			
			service_time[i] +=wasted; //total work by CPU
		}
		
		avg_wt=total_wt/n; //average waiting time
		
		//calculate turnaround time
		
		for(int i=0;i<n;i++)
		{
			tat[i]=bt[i]+wt[i]; //calculate turnaround time
			total_tat+=tat[i];
		}
		
		avg_tat=total_tat/n; //average turnaround time
		
		//calculate response time
		
		for(int i=1;i<n;i++)
		{
			rt[i]=wt[i]+at[i]; //calculate response time
			total_rt+=rt[i];
		}
		
		avg_rt = total_rt/n;
		
		//Utilization
		
		U= (total_bt/(total_bt+ wasted ))*100;
		
		//Throughput
		
		T=n/total_bt;
	}
void showData()
{	
	cout<<"\n\nProcess\t\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tResponse Time";
	for(i=0;i<n;i++)
    {
            
      cout<<"\nP"<<p[i]<<"\t\t"<<bt[i]<<"\t\t"<<at[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<"\t\t"<<rt[i];
    }
		
		
	cout<<"\n\nIdeal Time Of CPU: "<<wasted<<" units";
	cout<<"\n\nAverage Waiting Time: "<<avg_wt;
    cout<<"\n\nAverage Turnaround Time: "<<avg_tat;
	cout<<"\n\nAverage Response Time: "<<avg_rt;
		
	cout<<"\n\nUtilization: "<<U<<"%";
		
	cout<<"\n\nThroughput: "<<T;
	cout<<"\n\n";
}
	
	

int main()
{		
    getData();
    sortData();
    calculate();
	showData();
	return 0;
	
}
