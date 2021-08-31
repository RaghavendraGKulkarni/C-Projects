#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct process
{
    int id;
    int arrivalTime;
    int burnTime;
    int priority;
    int startTime;
    int waitTime;
    int turnAroundTime;
};
typedef struct process process;

struct schedule
{
    process* processes;
    int numberOfProcesses;
};
typedef struct schedule schedule;

void readProcesses(schedule *s,FILE *in)
{
    int i;
    fscanf(in,"%d",&s->numberOfProcesses);
    s->processes=(process*)calloc(s->numberOfProcesses+1,sizeof(process));
    for(i=1;i<=s->numberOfProcesses;i++)
        fscanf(in,"%d %d %d %d",&s->processes[i].id,&s->processes[i].arrivalTime,&s->processes[i].burnTime,&s->processes[i].priority);
    return;
}

void showProcesses(schedule s,FILE *out)
{
    int i;
    fprintf(out,"Process ID\tArrival Time\tBurn Time\tPriority\tStart Time\tWait Time\tTurn Around Time\n");
    for(i=1;i<=s.numberOfProcesses;i++)
        fprintf(out,"%d\t\t\t%d\t\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n",s.processes[i].id,s.processes[i].arrivalTime,s.processes[i].burnTime,s.processes[i].priority,s.processes[i].startTime,s.processes[i].waitTime,s.processes[i].turnAroundTime);
    return;
}

void equate(process *a,process *b)
{
    a->id=b->id;
    a->arrivalTime=b->arrivalTime;
    a->burnTime=b->burnTime;
    a->priority=b->priority;
    a->startTime=b->startTime;
    a->waitTime=b->waitTime;
    a->turnAroundTime=b->turnAroundTime;
    return;
}

void heapify(schedule *s)
{
    int i,j,k;
    bool heap;
    process p;
    for(i=s->numberOfProcesses/2;i>=1;i--)
    {
        k=i;
        equate(&p,s->processes+k);
        heap=false;
        while(!heap && 2*k<=s->numberOfProcesses)
        {
            j=2*k;
            if(j<s->numberOfProcesses && (s->processes[j].arrivalTime>s->processes[j+1].arrivalTime || (s->processes[j].arrivalTime==s->processes[j+1].arrivalTime && s->processes[j].burnTime>s->processes[j+1].burnTime)))
                j++;
            if(p.arrivalTime<s->processes[j].arrivalTime || (p.arrivalTime==s->processes[j].arrivalTime && p.burnTime<=s->processes[j].burnTime))
                heap=true;
            else
            {
                equate(s->processes+k,s->processes+j);
                k=j;
            }
        }
        equate(s->processes+k,&p);
    }
    return;
}

schedule nonPreemptiveSJF(schedule s,float *awt,float *atat)
{
    int size=0,time=0;
    process p;
    schedule s1;
    s1.numberOfProcesses=0;
    s1.processes=(process*)calloc(s.numberOfProcesses+1,sizeof(process));
    while(s.numberOfProcesses>0)
    {
        heapify(&s);
        s.processes[1].startTime=time;
        s.processes[1].waitTime=s.processes[1].startTime-s.processes[1].arrivalTime;
        s.processes[1].turnAroundTime=s.processes[1].burnTime+s.processes[1].waitTime;
        *awt+=s.processes[1].waitTime;
        *atat+=s.processes[1].turnAroundTime;
        time+=s.processes[1].burnTime;
        s1.numberOfProcesses++;
        equate(s1.processes+s1.numberOfProcesses,s.processes+1);
        equate(&p,s.processes+1);
        equate(s.processes+1,s.processes+s.numberOfProcesses);
        equate(s.processes+s.numberOfProcesses,&p);
        s.numberOfProcesses--;
    }
    s.numberOfProcesses=size;
    return s1;
}

int main()
{
    FILE *in,*out;
    schedule s;
    int *order=NULL;
    float awt=0,atat=0;
    in=fopen("Input.txt","r");
    readProcesses(&s,in);
    fclose(in);
    s=nonPreemptiveSJF(s,&awt,&atat);
    out=fopen("Output.txt","w");
    fprintf(out,"Schedule according to Non-Preemptive Shortest Job First:-\n");
    showProcesses(s,out);
    fprintf(out,"Average Waiting Time=%.2f\nAverage Turn Around Time=%.2f",awt/s.numberOfProcesses,atat/s.numberOfProcesses);
    fclose(out);
    free(order);
    return 0;
}
